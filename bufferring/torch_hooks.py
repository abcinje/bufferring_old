from bufferring.mpi import size, rank
from bufferring import message, mpi, ptable
from bufferring.compression import Compression
import queue
import torch

class _DistributedOptimizer(torch.optim.Optimizer):
    def __init__(self, params, named_parameters, compression, threshold):
        super(self.__class__, self).__init__(params)
        self._compression = compression
        self._threshold = threshold
        
        if named_parameters is not None:
            named_parameters = list(named_parameters)
        else:
            named_parameters = [('allreduce.noname.%s' % i, v)
                                for param_group in self.param_groups
                                for i, v in enumerate(param_group['param'])]

        if any([not isinstance(p, tuple) for p in named_parameters]):
            raise ValueError('named_parameters should be a sequence of '
                             'tuples (name, parameter), usually produced by '
                             'model.named_parameters().')

        dups = _DistributedOptimizer.find_duplicates([k for k, _ in named_parameters])
        if len(dups) > 0:
            raise ValueError('Parameter names in named_parameters must be unique. '
                             'Found duplicates: %s' % ', '.join(dups))

        all_param_ids = {id(v)
                         for param_group in self.param_groups
                         for v in param_group['params']}
        named_param_ids = {id(v) for k, v in named_parameters}
        unnamed_param_ids = all_param_ids - named_param_ids
        if len(unnamed_param_ids):
            raise ValueError('named_parameters was specified, but one or more model '
                             'parameters were not named. Python object ids: '
                             '%s' % ', '.join(str(id) for id in unnamed_param_ids))

        self._parameter_names = {v: k for k, v in sorted(named_parameters)}

        # MPI
        names = [self._parameter_names.get(p)
                 for param_group in self.param_groups
                 for p in param_group['params']]

        mpi.send_q = queue.Queue()
        mpi.recv_q = {name: queue.Queue() for name in names}
        mpi.send_proc.start()
        mpi.recv_proc.start()

        self._grad_accs = []
        self._requires_update = set()
        if size > 1:
            self._register_hooks()

        self._table = ptable.ProgressTable(size, rank, names)

    @staticmethod
    def find_duplicates(lst):
        seen = set()
        dups = set()
        for el in lst:
            if el in seen:
                dups.add(el)
            seen.add(el)
        return dups

    def _register_hooks(self):
        for param_group in self.param_groups:
            for p in param_group['params']:
                if p.requires_grad:
                    p.grad = p.data.new(p.size()).zero_()
                    self._requires_update.add(p)
                    p_tmp = p.expand_as(p)
                    grad_acc = p_tmp.grad_fn.next_functions[0][0]
                    grad_acc.register_hook(self._make_hook(p))
                    self._grad_accs.append(grad_acc)

    def _allreduce_grad_async(self, p):
        name = self._parameter_names.get(p)
        tensor = p.grad
        tensor_compressed, ctx = self._compression.compress(tensor)
        
        # 1. Send gradients and update ptable
        cycle = self._table.get_my_cycle(name)
        send_msg = message.Message(rank, cycle, name, tensor_compressed)
        mpi.send_q.put(send_msg)
        self._table.update(rank, name)

        # 2. Apply received (possibly multiple) updates
        #    and block until the staleness goes below the threshold
        count = 0
        while True:
            try:
                while True:
                    recv_msg = mpi.recv_q[name].get_nowait()
                    recv_tensor = self._compression.decompress(recv_msg.grad, ctx)
                    assert tensor.size() == recv_tensor.size()
                    tensor += recv_tensor
                    count += 1 # number of received tensors
                    self._table.update(recv_msg.src, recv_msg.name)
            except queue.Empty:
                if not self._table.blocked(self._threshold):
                    break

        if count > 0:
            tensor /= count + 1
            p.grad.set_(tensor)

    def _make_hook(self, p):
        def hook(*ignore):
            assert not p.grad.requires_grad
            self._allreduce_grad_async(p)
        return hook

def DistributedOptimizer(optimizer, named_parameters=None,
                         compression=Compression.none,
                         threshold=5):
    cls = type(optimizer.__class__.__name__, (optimizer.__class__,),
        dict(_DistributedOptimizer.__dict__))
    return cls(optimizer.param_groups, named_parameters, compression, threshold)

def broadcast_state(obj, root=0):
    if rank == root:
        state_dict = obj.state_dict()
    else:
        state_dict = None
    
    state_dict = mpi.bcast(state_dict, root)

    if rank != root:
        obj.load_state_dict(state_dict)

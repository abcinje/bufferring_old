from queue import Empty
from common.message import Message
from common.mpi import comm, size, rank
from common.mpi import send_q, recv_q
from common.ptable import ProgressTable
import tensorflow as tf

cycle = 0
table = ProgressTable(size, rank)

def reduce(tensor):
    if isinstance(tensor, tf.IndexedSlices):
        raise NotImplementedError('BufferRing does not support sparse tensors.')

    # 1. Send gradients and update ptable for my cycle
    global cycle
    cycle += 1
    send_msg = Message(rank, cycle) # TODO: Send gradients together
    send_q.put(send_msg)
    table.update(rank)

    # 2. Apply received (possibly multiple) updates
    #    and block until the staleness goes below the threshold
    while True:
        try:
            while True:
                recv_msg = recv_q.get_nowait()
                # tensor += recv_msg.grads TODO: Aggregate received gradients
                table.update(recv_msg.src)
        except Empty:
            if table.bounded(5):
                break

    return tensor

def _make_reduce_grads_fn(name):
    def reduce_grads(grads):
        with tf.name_scope(name + '_reduce'):
            return [reduce(grad)
                    if grad is not None else grad
                    for grad in grads]
                     
    return reduce_grads                    

try:
    # TensorFlow 2.x
    _LegacyOptimizer = tf.compat.v1.train.Optimizer
except AttributeError:
    try:
        # TensorFlow 1.x
        _LegacyOptimizer = tf.train.Optimizer
    except AttributeError:
        # Future TensorFlow versions
        _LegacyOptimizer = None

assert _LegacyOptimizer is not None

class DistributedOptimizer(_LegacyOptimizer):
    def __init__(self, optimizer, name=None, use_locking=False):
        if name is None:
            name = 'Distributed{}'.format(type(optimizer).__name__)
        super(DistributedOptimizer, self).__init__(name=name, use_locking=use_locking)

        self._optimizer = optimizer
        self._reduce_grads = _make_reduce_grads_fn(name)

    def compute_gradients(self, *args, **kwargs):
        gradients = self._optimizer.compute_gradients(*args, **kwargs)
        if size > 1:
            grads, vars = zip(*gradients)
            avg_grads = self._reduce_grads(grads)
            return list(zip(avg_grads, vars))
        else:
            return gradients

    def apply_gradients(self, *args, **kwargs):
        return self._optimizer.apply_gradients(*args, **kwargs)

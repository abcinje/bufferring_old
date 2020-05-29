from mpi4py import MPI
import threading

assert MPI.Query_thread() == MPI.THREAD_MULTIPLE

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

send_q = None
recv_q = None

def sender():
    while True:
        msg = send_q.get()
        comm.send(msg, dest=(rank+1)%size)

def receiver():
    while True:
        msg = comm.recv(source=(rank-1)%size)
        recv_q[msg.name].put(msg)
        if msg.src != (rank+1)%size:
            send_q.put(msg)

send_thr = threading.Thread(target=sender)
recv_thr = threading.Thread(target=receiver)

def bcast(data, root):
    return comm.bcast(data, root)

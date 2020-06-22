from mpi4py import MPI
import torch
import bfr_core

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

def init(names, thresh):
    bfr_core.init(MPI._addressof(comm), names, thresh)

def deinit():
    bfr_core.deinit()

def process(tensor, name):
    bfr_core.process(tensor, name)

def bcast(obj, root):
    return comm.bcast(obj, root)

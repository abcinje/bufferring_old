from mpi4py import MPI
import ctypes
import os

_libdir = os.path.dirname(os.path.abspath(__file__)) + '/libmpi'
_lib = ctypes.cdll.LoadLibrary(os.path.join(_libdir, 'libmpi.so'))

if MPI._sizeof(MPI.Comm) == ctypes.sizeof(ctypes.c_int):
    MPI_Comm = ctypes.c_int
else:
    MPI_Comm = ctypes.c_void_p

comm = MPI.COMM_WORLD

def init(comm):
    comm_ptr = MPI._addressof(comm)
    comm_val = MPI_Comm.from_address(comm_ptr)
    _lib.init(comm_val)

# Do not call this function
def deinit():
    _lib.deinit()

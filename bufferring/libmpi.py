from mpi4py import MPI
import ctypes
import os
import pickle

_libdir = os.path.dirname(os.path.abspath(__file__)) + '/libmpi'
_lib = ctypes.cdll.LoadLibrary(os.path.join(_libdir, 'libmpi.so'))

if MPI._sizeof(MPI.Comm) == ctypes.sizeof(ctypes.c_int):
    MPI_Comm = ctypes.c_int
else:
    MPI_Comm = ctypes.c_void_p

comm = MPI.COMM_WORLD

#######################
# Type Specifications #
#######################

# put()
_lib.put.restype = None
_lib.put.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int)

# get_nowait_fetch()
_lib.get_nowait_fetch.restype = ctypes.c_bool
_lib.get_nowait_fetch.argtypes = (ctypes.c_char_p,)

# get_nowait_len()
_lib.get_nowait_len.restype = ctypes.c_int
_lib.get_nowait_len.argtypes = None

# get_nowait_data()
_lib.get_nowait_data.restype = ctypes.c_void_p
_lib.get_nowait_data.argtypes = None

# get_nowait_free()
_lib.get_nowait_free.restype = None
_lib.get_nowait_free.argtypes = None

###################
# Python Wrappers #
###################

# init()
def init(comm, names):
    bytes_list = [bytes(name, 'utf-8') for name in names]
    arr = (ctypes.c_char_p * len(names))()
    arr[:] = bytes_list

    comm_ptr = MPI._addressof(comm)
    comm_val = MPI_Comm.from_address(comm_ptr)
    _lib.init(comm_val, arr, len(names))

# deinit()
# Do not call this function
def deinit():
    _lib.deinit()

# put()
def put(name, obj):
    encoded = pickle.dumps(obj)
    _lib.put(bytes(name, 'utf-8'), encoded, len(encoded))

# get_nowait()
def get_nowait(name):
    if not _lib.get_nowait_fetch(bytes(name, 'utf-8')):
        raise BufferError

    length = _lib.get_nowait_len()
    encoded = ctypes.string_at(_lib.get_nowait_data(), size=length)
    obj = pickle.loads(encoded)
    _lib.get_nowait_free()
    return obj

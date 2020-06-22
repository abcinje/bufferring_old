import os
from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CppExtension

os.environ['CC'] = 'mpicc'
os.environ['CXX'] = 'mpicxx'

sources = ['comm.cpp', 'interface.cpp', 'message.cpp', 'ntable.cpp', 'ptable.cpp', 'torchtensor.cpp']

setup(
    name='bfr_core',
    ext_modules=[CppExtension('bfr_core', sources)],
    cmdclass={'build_ext': BuildExtension}
)

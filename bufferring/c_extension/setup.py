from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CppExtension

setup(
    name='bfr_cpp',
    ext_modules=[
        CppExtension('bfr_cpp', ['bfr.cpp']),
    ],
    cmdclass={
        'build_ext': BuildExtension
    })

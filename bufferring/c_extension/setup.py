from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CppExtension

setup(
    name='bfr_cpp',
    ext_modules=[
        CppExtension('brf_cpp', ['brf.cpp']),
    ],
    cmdclass={
        'build_ext': BuildExtension
    })

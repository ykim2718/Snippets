from distutils.core import setup, Extension

sourceFiles = ['test.cpp', 'test_wrap.cxx']
includeDirs = []

_EM = Extension(
    '_yDrillSWIG2',
    sources=sourceFiles,
    include_dirs=includeDirs,
    swig_opts=['-c++'],
    extra_compile_args=['/EHsc']
)
setup(
    name='yDrillSWIG2',
    version='0.1',
    author='Y. Kim',
    description="Drill SWIG for Cpp interfacing",
    ext_modules=[_EM],
    py_modules=['yDrillSWIG2']
)

from distutils.core import setup, Extension

sourceFiles = ['example.c', 'example_wrap.c']
includeDirs = []
swigOptions = []

_EM = Extension(
    '_yDrillSWIG3',
    sources=sourceFiles,
    include_dirs=includeDirs,
    swig_opts=swigOptions,
    extra_compile_args=['/EHsc']
)
setup(
    name='yDrillSWIG3',
    version='0.1',
    author='Y. Kim',
    description="Drill SWIG for array return",
    ext_modules=[_EM],
    py_modules=['yDrillSWIG3']
)

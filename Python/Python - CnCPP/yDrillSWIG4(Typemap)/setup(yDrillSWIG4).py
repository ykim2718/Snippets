from distutils.core import setup, Extension

sourceFiles = ['yswig4.c', 'yswig4_wrap.c']
includeDirs = []
swigOptions = []

_EM = Extension(
    '_yDrillSWIG4',
    sources=sourceFiles,
    include_dirs=includeDirs,
    swig_opts=swigOptions,
    extra_compile_args=['/EHsc']
)
setup(
    name='yDrillSWIG4',
    version='2016.4.6',
    author='Y. Kim',
    description="y Drill SWIG Typemap",
    ext_modules=[_EM],
    py_modules=['yDrillSWIG4']
)

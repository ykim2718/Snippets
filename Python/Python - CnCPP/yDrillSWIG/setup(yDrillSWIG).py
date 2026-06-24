from distutils.core import setup, Extension
import numpy

try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

includeDirs = [numpy_include]
sourceFiles = ['yDrillSWIG_wrap.c', 'yDrillSWIG.c']

_EM = Extension('_yDrillSWIG',
                sources=sourceFiles,
                include_dirs=includeDirs
                )
setup(name='yDrillSWIG',
      version='0.1',
      author='kY. Kim',
      description="""Drill SWIG""",
      ext_modules=[_EM],
      py_modules=["yDrillSWIG"]
      )

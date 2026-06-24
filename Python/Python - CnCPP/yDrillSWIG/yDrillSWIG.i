%module yDrillSWIG
%include "cpointer.i"
%include "carrays.i"
%pointer_functions(int, intPointer);
%array_functions(int,intArray);

//http://docs.scipy.org/doc/numpy/reference/swig.interface-file.html
//http://stackoverflow.com/questions/30259591/swig-and-multidimensional-arrays
%{
   #define SWIG_FILE_WITH_INIT
   #include "yDrillSWIG.h"
%}
%include "numpy.i"
%init %{
   import_array();
%}
%apply (int * IN_ARRAY2, int DIM1, int DIM2) {(int *array2d, int nRow, int nCol)};

%include "yDrillSWIG.h"
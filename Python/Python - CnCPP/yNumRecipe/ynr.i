%module yNumRecipe

%include "cpointer.i"
%pointer_functions(double,doublePointer);

%include "carrays.i"
%array_functions(double,doubleArray);

%header %{
#include "yCore.h"
#include "yNumber.h"
#include "yNrecipe.h"
#include "yNr4.h"
%}

%typemap(out) double* yZscore2d {
  int i;
  //$1, $1_dim0, $1_dim1
  $result = PyList_New(2);
  for (i = 0; i < 2; i++) {
    PyObject *o = PyFloat_FromDouble((double) $1[i]);
    PyList_SetItem($result,i,o);
  }
}

/*
[http://www.swig.org/Doc1.3/Preprocessor.html]
Unlike, #include, %include includes each file once (and will not reload
the file on subsequent %include declarations). Therefore, it is not
necessary to use include-guards in SWIG interfaces.

%include "yCore.h"
%include "yNumber.h"
%include "yNrecipe.h" */
typedef struct { double mean, stdev; } UVNParameter; /* 2016.3.31 */
typedef struct { double m_x, s_x, m_y, s_y, r; } BVNParameter; /* 2016.3.31 */
%include "yNr4.h"

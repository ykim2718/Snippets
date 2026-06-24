/*
http://www.swig.org/Doc3.0/SWIGDocumentation.html#Typemaps_special_variables
*/
%module yDrillSWIG4
%{
  extern double *f1();
  extern double *f2();
  extern double  f3();
%}

%typemap(out) double * { /* only to function returning double*, f1(), f2() */
  int i;
  // $1, $1_dim0, $1_dim1
  $result = PyList_New(2);
  for (i=0;i<2;i++){
    PyObject *o= PyFloat_FromDouble((double)$1[i]);
    PyList_SetItem($result,i,o);
  }
}

%typemap(out) double f3 { /* only to double f3() */
  $result = PyFloat_FromDouble ((double)($1+1.0));
}

%include "yswig4.c"
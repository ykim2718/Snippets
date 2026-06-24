#include "Python.h"

static PyObject *ErrorObject;

static char add_doc[]="add two integers";
static PyObject* sample_add(PyObject* self, PyObject* args)
{
   int a,b,r;
   if (!PyArg_ParseTuple(args,"ii",&a,&b))
      return NULL;
   r=a+b;
   return Py_BuildValue("i",r);
};

static char area_doc[]="area (width, height)";
static PyObject* sample_area(PyObject* self, PyObject* args, PyObject* kwdict)
{
   static char *kwlist[]={"width","height",NULL};
   int width,height,r;
   if (!PyArg_ParseTupleAndKeywords(args,kwdict,"ii",kwlist,&width,&height))
      return NULL;
   r=width*height;
   return Py_BuildValue("i",r);
};

static struct PyMethodDef _sample_methods[]={
   {"add",sample_add,METH_VARARGS,add_doc},
   {"area",sample_area,METH_VARARGS|METH_KEYWORDS,area_doc},
   {NULL} /* end of module method table */
};

static struct PyModuleDef _sample_module={
   PyModuleDef_HEAD_INIT,
   "_sample", /* module name */
   "This is a module doc",
   -1,
   _sample_methods
};

PyMODINIT_FUNC
PyInit__sample(void)
{
   PyObject *m;
   m=PyModule_Create(&_sample_module);
   return m;
};
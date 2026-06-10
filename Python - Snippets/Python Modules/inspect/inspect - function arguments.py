"""
y, inspect - function arguments.py, 2018.8.8
"""

import inspect


def my_func(a, b, *my_args, c=None, d=1, **my_kwargs):
    pass


argspec = inspect.getfullargspec(my_func)
print(argspec)
print(argspec.args)
print(argspec.kwonlyargs)
print('argspec.kwonlydefaults.values() =', argspec.kwonlydefaults.values())
print(argspec.varargs)
print(argspec.varkw)

signature = inspect.signature(my_func)
print(signature, type(signature), signature.parameters['a'])

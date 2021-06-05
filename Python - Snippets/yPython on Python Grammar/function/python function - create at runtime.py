"""
y, python function - create at runtime.py, 2019.11.20
https://stackoverflow.com/questions/11291242/python-dynamically-create-function-at-runtime
"""

import types


def create_function(f, name):
    code = types.CodeType(f.__code__.co_argcount,
                          f.__code__.co_kwonlyargcount,
                          f.__code__.co_nlocals,
                          f.__code__.co_stacksize,
                          f.__code__.co_flags,
                          f.__code__.co_code,  # compiled byte code
                          f.__code__.co_consts,
                          f.__code__.co_names,
                          f.__code__.co_varnames,
                          f.__code__.co_filename,
                          name,
                          f.__code__.co_firstlineno,
                          f.__code__.co_lnotab,
                          f.__code__.co_freevars,
                          f.__code__.co_cellvars)

    return types.FunctionType(code, f.__globals__, name=name)


def old_func(a, b, c=30):
    print(a, b, c)


new_func = create_function(old_func, 'new_func')

print(repr(new_func))
print(new_func.__name__)

new_func(1, 2, 3)

import inspect

argspec = inspect.getfullargspec(new_func)  # wraps not working for inspect.getfullargspec() !!!
arguments = argspec.args + argspec.kwonlyargs
print('>>', arguments)

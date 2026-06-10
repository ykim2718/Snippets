"""
y, inspect - get kwarg default value of function.py, 2019.1.21
"""

import inspect


def my_func(a, b, *my_args, c=None, d=1, **my_kwargs):
    pass


kwarg = 'd'
argspec = inspect.getfullargspec(my_func)
j = argspec.kwonlyargs.index(kwarg)
default_value = list(argspec.kwonlydefaults.values())[j]
print(default_value)


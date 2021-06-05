"""
y, inspect - class member func arguments.py, 2019.1.3
"""

print(__doc__)

import inspect


class Klass:
    def __init__(self, a, b, *my_args, c=None, d=1, **my_kwargs):
        pass

Glass = Klass

argspec = inspect.getfullargspec(Glass.__init__)
print(argspec)
print(argspec.args)
print(argspec.kwonlyargs)
print(argspec.kwonlydefaults.values())
print(argspec.varargs)
print(argspec.varkw)

signature = inspect.signature(Glass.__init__)
print(signature, type(signature), signature.parameters['a'])



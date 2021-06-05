"""
y, python decorator - assign_kwargs_to_class_attributes.py, 2019.1.3
"""

print(__doc__)

import inspect


def assign_kwargs_to_class_attributes(f):  # arguments here can take function and decorator arguments !!!
    """ y, 2019.1.3 """

    def decorated(*args, **kwargs):  # arguments here takes function arguments !!!
        signature = inspect.signature(f)
        assert 'self' in signature.parameters, 'make sure of the sure in the class'
        self = args[0]
        for k, v in signature.parameters.items():
            if v.kind == inspect.Parameter.KEYWORD_ONLY and v.default is None:
                if kwargs.get(k, None) is None:
                    kwargs[k] = getattr(self, k, None)
            # print('>>', type(args), len(args), args)
            # print('>>', type(kwargs), len(kwargs), kwargs)
            return f(*args, **kwargs)
    return decorated

class Klass:

    a = 1
    b = 2
    c = 3
    d = 4

    @assign_kwargs_to_class_attributes
    def __init__(self, a, *args, b=0, c=None, d=None, e=None, **kwargs):
        print(a, b, c, d, e)

Klass(10, c=30)
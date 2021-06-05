"""
y, python decorator - assign_kwargs_from_class_attributes.py, 2019.1.3
"""

print(__doc__)

import inspect


def assign_kwargs_from_class_attributes(*d_args, **d_kwargs):
    """ y, 2019.1.3 """

    def wrap(f):
        def wrapped_f(*f_args, **f_kwargs):
            signature = inspect.signature(f)
            assert 'self' in signature.parameters, 'make sure of the sure in the class'
            self = f_args[0]
            skips = d_kwargs.get('skips', [])
            assert isinstance(skips, (list, tuple))
            for k, v in signature.parameters.items():
                if v.kind == inspect.Parameter.KEYWORD_ONLY and hasattr(self, k) and k in f_kwargs and k not in skips:
                    setattr(self, k, f_kwargs[k])
            # print('decorator arguments:', d_args, d_kwargs)
            # print('function arguments:', f_args, f_kwargs)
            return f(*f_args, **f_kwargs)
        return wrapped_f
    return wrap


class Klass:

    a = 1
    b = 2
    c = 3
    d = 4

    @assign_kwargs_from_class_attributes(skips=['c'])
    def __init__(self, a, *f_args, b=0, c=None, d=None, e=None, **f_kwargs):
        print(a, b, c, d, e)

k = Klass(10, c=30, d=40)
print(k.a, k.b, k.c, k.d)

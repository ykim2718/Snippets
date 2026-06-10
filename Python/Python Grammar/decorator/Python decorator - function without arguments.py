"""
y, Python decorator - function without arguments.py, 2016.6.11
    2019.1.3
"""

print(__doc__)


def decorator(fn):
    def decorated(*args, **kwargs):  # argument here takes function arguments !!!
        print(type(args), len(args), args)
        print(type(kwargs), len(kwargs), kwargs)
        return fn(*args, **kwargs)

    return decorated


def foo(a, b, c):
    print(a)
    print(b)
    print(c)


foo(1, 2, 3)

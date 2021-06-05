"""
y, python decorator - simple form.py, 2019.9.15, 10.23
https://www.codementor.io/sheena/advanced-use-python-decorators-class-function-du107nxsv
"""

from functools import wraps


def decorator(fn):
    @wraps(fn)
    def decorated(*args, **kwargs):
        # before ...
        return fn(*args, **kwargs)
    return decorated


@decorator
def foo(a, b, c):
    """ foo ooo oooo """
    print(a)
    print(b)
    print(c)


foo(1, 2, 3)

print(foo.__name__)
print(foo.__doc__)
print(foo.__module__)

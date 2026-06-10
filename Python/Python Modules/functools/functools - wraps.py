"""
y, functools - wraps.py, 2019.1.15, 11.20
https://docs.python.org/3.7/library/functools.html
"""

from functools import wraps


def my_decorator(f):
    @wraps(f)
    def wrapper(*args, **kwds):
        print('>> Calling decorated function')
        return f(*args, **kwds)

    # wrapper.__code__.co_varnames = f.__code__.co_varnames
    return wrapper


@my_decorator
def example(a, b=2):
    """Doc string"""
    print('>> Called example function', a, b)


example(1)
help(example)
print('>>', example.__name__)

import inspect

argspec = inspect.getfullargspec(example)  # wraps not working for inspect.getfullargspec() !!!
arguments = argspec.args + argspec.kwonlyargs
print('>>', arguments)

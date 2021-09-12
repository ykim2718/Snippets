"""
y, 2021.9.12
inspect - decorated function arguments.py
"""

import inspect
import functools


def my_decorator(f):

    @functools.wraps(f)
    def wrapper(*args, **kwargs):
        argspec = inspect.getfullargspec(f)
        print(f"getfullargspec={argspec}")
        signature = inspect.signature(f)
        print(f"signature={signature}")
        print(f"argspec.args={argspec.args}")
        print(f"argspec.kwargs={argspec.kwonlyargs}")
        j = argspec.args.index('b')
        args = list(args)
        args[j] *= 10
        args = tuple(args)
        result = f(*args, **kwargs)
        return result

    return wrapper


@my_decorator
def my_func(a, b, *my_args, c=None, d=1, **my_kwargs):
    return a, b, c, d


r = my_func(1, 2)
print(f"r={r}")

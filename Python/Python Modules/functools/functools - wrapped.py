"""
y,  2024.5.2
functools - wrapped.py
https://stackoverflow.com/questions/75582932/python-how-can-i-print-the-function-name-of-a-partial-function?newreg=930ce90b7e6a4d04b3465a75355fa694
"""

from functools import partial, update_wrapper
retry_queue = []


def wrapped_partial(func, *args, **kwargs):
    """
    y,  2024.5.2

    References
    ----------
    [1] https://stackoverflow.com/questions/75582932/python-how-can-i-print-the-function-name-of-a-partial-function
        ?newreg=930ce90b7e6a4d04b3465a75355fa694
    """
    partial_func = partial(func, *args, **kwargs)
    update_wrapper(partial_func, func)
    return partial_func


def foo(args=1):
    return None


print(f"{foo.__name__=}")
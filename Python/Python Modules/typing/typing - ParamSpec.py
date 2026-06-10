"""
y, 2022.6.18
https://docs.python.org/3/library/typing.html#typing.ParamSpec
"""
from platform import python_version
print(python_version())
assert python_version() >= '3.10.5'

from collections.abc import Callable
from typing import TypeVar, ParamSpec
import logging

T = TypeVar('T')
P = ParamSpec('P')


def add_logging(f: Callable[P, T]) -> Callable[P, T]:
    '''A type-safe decorator to add logging to a function.'''

    def inner(*args: P.args, **kwargs: P.kwargs) -> T:
        logging.info(f'{f.__name__} was called')
        return f(*args, **kwargs)

    return inner


@add_logging
def add_two(x: float, y: float) -> float:
    '''Add two numbers together.'''
    return x + y

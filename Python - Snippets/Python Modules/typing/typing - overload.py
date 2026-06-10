"""
y, 2022.6.18, 11.4
typing - overload.py
https://docs.python.org/3.9/library/typing.html#typing.overload
https://peps.python.org/pep-0484/#function-method-overloading
https://stackoverflow.com/questions/52034771/overload-decorator-in-typings-module-doesnt-seem-to-behave-as-expected
https://docs.python.org/3/library/typing.html
    The @overload-decorated definitions are for the benefit of the type checker only,
    since they will be overwritten by the non-@overload-decorated definition,
    while the latter is used at runtime but should be ignored by a type checker.
"""

import typing


class Klass:

    @typing.overload
    def __init__(self, a: int) -> None:
        print('int', a)

    @typing.overload
    def __init__(self, a: str) -> None:
        print('str', a)

    def __init__(self, a):
        print('actual', a)


Klass(123)
Klass('abc')


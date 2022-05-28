"""
y, 2022.5.28
python annotation - typing.py
"""

import typing


def f(
    a: typing.Union[int, None] = None
) -> int:
    print(a)
    return a


f(a=1)

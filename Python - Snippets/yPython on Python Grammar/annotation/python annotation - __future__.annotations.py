"""
y, 2022.5.28
python annotation - __future__.annotations.py
"""


from __future__ import annotations


def f(
    a: int | None = None
) -> [int[float]]:
    print(a)
    return a


f(a=1)
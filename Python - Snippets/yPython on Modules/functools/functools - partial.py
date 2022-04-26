"""
y, 2020.1.7, 2.2; 2022.4.26
functools - partial.py
"""

from functools import partial


def sum(a, b, c=3):
    print(a, b, c)


f = partial(sum, 10)
f(1)  # 10 1 3
f = partial(sum, b=10)
f(1)  # 1 10 3
f = partial(sum, a=10)
f(b=10)  # 10 10 3

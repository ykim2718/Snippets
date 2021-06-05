"""
y, 2020.1.7, 2.2
functools - partial.py
"""

from functools import partial


def sum(a, b, c=3):
    print(a, b, c)


f = partial(sum, 10)
f(1)
f = partial(sum, b=10)
f(1)
# f = partial(sum, a=10)  # TypeError: sum() got multiple values for argument 'a'

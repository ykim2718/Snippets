"""
y, 2020.1.7, 2.2; 2022.4.26; 2025.9.11
functools - partial.py
"""

from functools import partial


def sum(a, b, c=3):
    print(a, b, c)


f = partial(sum, 10)
f(2)  # 10 2 3
f = partial(sum, b=20)
f(1)  # 1 20 3
f = partial(sum, a=10)
f(b=2)  # 10 2 3
f = partial(sum, a=10)
f(2)  # TypeError: sum() got multiple values for argument 'a'

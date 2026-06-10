"""
y, 2021.37
itertools - starmap.py
"""

import itertools

a = [1, 2, 3]


def my_func(x):
    return x * 2


for j in itertools.starmap(my_func, [(x,) for x in a]):
    print(j)

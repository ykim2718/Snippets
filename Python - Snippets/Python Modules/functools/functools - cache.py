"""
y, 2022.6.18
functools - cache.py
https://docs.python.org/ko/3/library/functools.html#functools.cached
"""

import functools
import timeit


@functools.cache
def factorial(n):
    return n * factorial(n - 1) if n else 1


f = functools.cache(factorial)


def f1():
    factorial(10)
    factorial(10)
    factorial(10)


def f2():
    factorial(10)
    factorial(9)
    factorial(8)


iteration = 1000000
print(timeit.timeit('factorial(10)', setup='from __main__ import factorial', number=iteration))
print(timeit.timeit('factorial(7)', setup='from __main__ import factorial', number=iteration))
print(timeit.timeit('factorial(5)', setup='from __main__ import factorial', number=iteration))
print(timeit.timeit('factorial(10)', setup='from __main__ import factorial', number=iteration))
print(timeit.timeit('f1()', setup='from __main__ import f1', number=iteration))
print(timeit.timeit('f2()', setup='from __main__ import f2', number=iteration))

"""
0.0664472
0.0596092
0.06105859999999999
0.06098379999999998
0.27812100000000006
0.27382609999999996
I can hardly see any change in speed :( -_-
"""

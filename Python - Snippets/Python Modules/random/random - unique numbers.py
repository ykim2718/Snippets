"""
y, random - unique numbers.py, 2019.10.18
https://stackoverflow.com/questions/22842289/generate-n-unique-random-numbers-within-a-range
"""


import itertools
import random


def unique_random_int(low, high, size=3):

    count = high - low
    assert count % size == 0, "count (high-low) should be multiple of size, but count={}, size={}".format(count, size)
    iterable = iter(random.sample(range(low, high), count))  # iter(np.random.permutation(count))
    for j in range(count // size):
        a = []
        for k in range(size):
            a.append(next(iterable))
        yield a


generator = unique_random_int(0, 9, 3)
for x in generator:
    print(x)


"""
[9, 5, 8]
[1, 6, 3]
[2, 0, 4]
"""


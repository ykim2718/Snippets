"""
y, itertools - tee (2).py, 2019.10.18
"""

import itertools


def my_iterator(array):

    print('outside')
    for a in array:
        print('inside')
        yield a


first_it, second_it = itertools.tee(my_iterator([1, 2, 3]))
for x in first_it:
    print('1st >>', x)
for x in second_it:
    print('2nd >>', x)

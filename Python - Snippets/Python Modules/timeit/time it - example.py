"""
y, time it - example.py, 2017.6.17

Fastest way to update a dictionary in python
    https://stackoverflow.com/questions/4156392/fastest-way-to-update-a-dictionary-in-python

"""

import timeit

setup = """
import random
random.seed(0)
item_count = 100000
# divide key range by 5 to ensure lots of duplicates
items = [(random.randint(0, item_count/5), 0) for i in range(item_count)]
"""
in_dict = """
d = {}
for k, v in items:
    if k not in d:
        d[k] = v
"""
set_default = """
d = {}
for k, v in items:
    d.setdefault(k, v)
"""
straight_add = """
d = {}
for k, v in items:
    d[k] = v
"""
print('in_dict      ', timeit.Timer(in_dict, setup).timeit(1000))
print('set_default  ', timeit.Timer(set_default, setup).timeit(1000))
print('straight_add ', timeit.Timer(straight_add, setup).timeit(1000))

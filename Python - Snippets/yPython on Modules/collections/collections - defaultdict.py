"""
y, 2022.5.3
collections - defaultdict.py
https://docs.python.org/3/library/collections.html#collections.defaultdict
"""

from collections import defaultdict

d = defaultdict(int)
d['a'] += 1
print(d)  # defaultdict(<class 'int'>, {'a': 1})

d = defaultdict(list)
d['a'] += [1]
print(d)  # defaultdict(<class 'list'>, {'a': [1]})


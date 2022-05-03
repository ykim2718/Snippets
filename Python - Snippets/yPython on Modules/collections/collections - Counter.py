"""
y, 2022.5.3
collections - Counter.py
https://docs.python.org/3/library/collections.html#counter-objects
"""

from collections import Counter

c = Counter()                           # a new, empty counter
c = Counter('gallahad')                 # a new counter from an iterable
print(c)  # Counter({'a': 3, 'l': 2, 'g': 1, 'h': 1, 'd': 1})
print(c['a'])  # 3
print(sorted(c.elements()))  # ['a', 'a', 'a', 'd', 'g', 'h', 'l', 'l']


c = Counter({'red': 4, 'blue': 2})      # a new counter from a mapping
print(c)  # Counter({'red': 4, 'blue': 2})


c = Counter(cats=4, dogs=8, cows=2)
print(c)  # Counter({'dogs': 8, 'cats': 4, 'cows': 2})
c['cats'] *= 10
print(c)  # Counter({'cats': 40, 'dogs': 8, 'cows': 2})
# r = c.total()  # python 3.10
# print(r)  # ...
a = c.most_common(2)
print(a)  # [('cats', 40), ('dogs', 8)]


c = Counter(a=4, b=2, c=0, d=-2)
d = Counter(a=1, b=2, c=3, d=4)
c.subtract(d)
print(c)  # Counter({'a': 3, 'b': 0, 'c': -3, 'd': -6})
c += d
print(c)  # Counter({'a': 4, 'b': 2})
c -= d
print(c)  # Counter({'a': 3})

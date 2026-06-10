"""
y, 2022.5.3 - 4
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

d = defaultdict(defaultdict)
print(f"{d.values()=}, {len(d.values())=}")  # dict_values([]), len(d.values())=0
d[1][1] = 1
d[1][2] = 2
d[2][3] = 3
print(f"{d.keys()=}")  # d.keys()=dict_keys([1, 2])
print(f"{d[1].values()=}")  # d[1].values()=dict_values([1, 2])
print(f"{d[2].values()=}")  # d[2].values()=dict_values([3])
print(f"{d[3]=}")  # d[3]=defaultdict(None, {})


class Klass:
    def __init__(self, a, b):
        self.a = a
        self.b = b


d = defaultdict(dict)
print(f"{d.values()=}")  # d.values()=dict_values([])
d[1] = Klass(1, 2)
d[2] = 2
d[3] |= dict(a=3)
print(f"{d=}")  # d=defaultdict(<class 'dict'>, {1: <__main__.Klass object at 0x000001B3D50B3F70>, 2: 2, 3: {'a': 3}})


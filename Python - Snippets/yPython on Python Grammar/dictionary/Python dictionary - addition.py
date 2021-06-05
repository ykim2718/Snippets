"""
y, 2016.7.4, Python - dictionary addition.py
"""

a = {'a': 1}
b = {'b': 2}
c = {'c': 3}

d = {}
d.update(a)
d.update(b)
d.update(c)
print(d)

d = dict(a, **b)
print(d)

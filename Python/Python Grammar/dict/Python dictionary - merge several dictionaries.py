"""
y, Python dictionary - merge several dictionaries.py, 2017.8.24

"""

a, b = dict(a=1, b=1), dict(b=2)
# assert len(set(a) ^ set(b)) == 0
# c = dict(**a, **b)
c = {**a, **b}
print(a, b, '>>', c)

a, b = dict(a=1), dict(b=2)
c = dict(a, **b)
print(a, b, '>>', c)

a, b = dict(a=1), dict(b=2)
c = a.update(b)
print(a, b, '>>', c)



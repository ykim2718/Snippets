"""
y, python class - namespace (1).py, 2018.9.4
"""


class Namespace:
    pass


ns = Namespace()
ns.a = 1
print(vars(ns))

ns.__dict__.update(dict(a=2, b=3))
print(vars(ns))

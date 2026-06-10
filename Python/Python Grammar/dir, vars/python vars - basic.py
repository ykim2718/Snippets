"""
y, python vars - basic.py, 2019.5.19
"""


class Silica:

    silica = "glass material"


class Glass(Silica):

    a = 1

    def __init__(self):

        self.b = 2


Glass.c = 30
g = Glass()
g.a = 40
g.__class__.d = 50
print(Glass.__dict__)  # base class dictionary
print(g.__dict__)  # class instance dictionary
print(g.__class__.__dict__)  # class base dictionary, same as Glass.__dict__
print(vars(g))  # same as g.__dict__
print(vars(Glass))  # same as g.__class__.__dict__
print(g.__class__.__mro__)

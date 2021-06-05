"""
y, Python - class with generalized init, 2016.6.9
http://www.dabeaz.com/py3meta/index.html
Some issues:
#1 No support for keyword args
#2 Missing calling signatures
"""


class Structure:
    _fields = []

    def __init__(self, *args):
        if len(args) != len(self._fields):
            raise TypeError('Wrong # args')
        for name, val in zip(self._fields, args):
            setattr(self, name, val)


class Stock(Structure):
    _fields = ['name', 'shares', 'price']


class Point(Structure):
    _fields = ['x', 'y']


class Host(Structure):
    _fields = ['address', 'port']


s = Stock('ACME', 50, 123.45)
print(s.name, s.shares, s.price)

p = Point(4, 5)
print(p.x, p.y)

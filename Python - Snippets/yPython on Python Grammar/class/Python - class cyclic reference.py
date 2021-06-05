"""
y, Python - class cyclic reference.py, 2016.6.24
Safely using destructors in Python
http://eli.thegreenplace.net/2009/06/12/safely-using-destructors-in-python
"""

import weakref


class FooType(object):
    def __init__(self, id, parent):
        self.id = id
        self.parent = weakref.ref(parent)
        print('Foo', self.id, 'born')

    def __del__(self):
        print('Foo', self.id, 'died')


class BarType(object):
    def __init__(self, id):
        self.id = id
        self.foo = FooType(id, self)
        print('Bar', self.id, 'born')

    def __del__(self):
        print('Bar', self.id, 'died')


b = BarType(12)

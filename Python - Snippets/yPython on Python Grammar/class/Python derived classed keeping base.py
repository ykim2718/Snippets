"""
y, Python - derived classed keeping base.py, 2016.6.8
"""


class Base:
    base = 0

    def __init__(self, source=None):
        if source is not None:
            print('this class name =', source.__class__.__name__)
            print('base class name =', source.__class__.__bases__[0].__name__)
            if source.__class__.__bases__[0].__name__ == 'Base':
                self.copy_init(source)

    def copy_init(self, other):
        self.base = other.base
        pass


class Derived1(Base):
    d1 = 0

    def add(self):
        self.base += 1


class Derived2(Base):
    pass


b = Base()
print(b.base)

d1 = Derived1(b)
d1.add()
print(b.base, d1.base)

d2 = Derived2(d1)
d2.base += 1
# error below because d2 base class "Base" does not have add() attribute !!
# print(d2.add())
print(b.base, d1.base, d2.base)

del d1
print(b.base, 'x', d2.base)

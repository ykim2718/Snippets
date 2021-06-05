"""
y, Python - class sharing container data.py, 2016.6.8
"""

import pandas as pd


class Base:
    base_int = 0  # immutable object, such as numbers and strings
    base_list = [0]  # container object, like tuple, list, set, dict

    def add(self):
        self.base_int += 1
        self.base_list[0] = self.base_int


class Derived1(Base):
    pass


class Derived2(Base):
    pass


b = Base()
d1 = Derived1()
d2 = Derived2()
print('d1', b.base_int, b.base_list, d1.base_int, d1.base_list)
print('d2', b.base_int, b.base_list, d2.base_int, d2.base_list)

d1.add()
d1.add()
print('after d1.add() twice')
print('d1', b.base_int, b.base_list, d1.base_int, d1.base_list)
print('d2', b.base_int, b.base_list, d2.base_int, d2.base_list)

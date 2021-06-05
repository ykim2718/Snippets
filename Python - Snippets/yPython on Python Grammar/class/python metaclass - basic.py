"""
y, Python metaclass - basic.py, 2017.5.12; 2021.1.15

"""

import abc


class Glass(metaclass=abc.ABCMeta):

    g = 'Glass'

    @abc.abstractmethod
    def print(self):
        pass

    @abc.abstractmethod
    def attr(self):
        pass

    @property
    @abc.abstractmethod
    def attr_1(self):
        pass


class Klass(Glass):

    k = 'Klass'

    def print(self):
        print(self.g, self.k)

    attr = 'attribute'
    attr_1 = 'attribute_1'


a = Klass()
print(type(a), a.__class__.__name__, a.attr, a.attr_1)
a.print()

"""
y, 2016.11.30, 12.1, python - abc basic.py
"""
import abc

class Base():

    b = 'b'

    def print0(self):
        pass


class BaseABC(Base, metaclass=abc.ABCMeta):

    @abc.abstractproperty
    def b(self):
        return 'bABC'

    @abc.abstractmethod
    def print0(self):
        print(0)

    def print1(self):
        print(1)


class Glass(BaseABC):

    @property
    def b(self):
        return 12.1

    def print0(self):
        pass

    def print2(self):
        print(2)


g = Glass()
print(issubclass(Glass, Base))
print(g.b)
g.print0()
g.print1()
g.print2()

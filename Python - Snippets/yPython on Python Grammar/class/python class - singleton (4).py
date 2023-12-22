"""
y, 2023.12.22
python class - singleton (4).py
https://www.geeksforgeeks.org/singleton-pattern-in-python-a-complete-guide/
"""


class SingletonClass(object):

    _b = []

    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(SingletonClass, cls).__new__(cls)
        return cls.instance


class Klass(SingletonClass):

    def __init__(self):
        print(f"{self.__class__.__name__=}")
        self._a = []

    def __repr__(self):
        return f"{self.__class__.__name__}(_a={self._a}, _b={self._b})"

    def add(self, x):
        self._a.append(x)
        self._b.append(x)


a = Klass()
a.add(1)
print(f"{a=}, {id(a)=}, {id(a._a)=}")  # [1]
b = Klass()
b.add(2)
print(f"{a=}, {id(a)=}, {id(a._a)=}")  # [2]
print(f"{b=}, {id(b)=}, {id(b._a)=}")  # [2]


"""
y, 2023.12.22; 2024.1.18, 5.12
python singleton class - new.py
https://www.geeksforgeeks.org/singleton-pattern-in-python-a-complete-guide/
"""


class SingletonClass(object):

    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, 'instance'):
            cls.instance = super(SingletonClass, cls).__new__(cls)
        return cls.instance


class Klass(SingletonClass):

    _instantiated = False
    _args = []
    _kwargs = dict()

    def __init__(self, *args, **kwargs):
        print(f"{self.__class__.__name__}.__init__({args=}, {kwargs=}): {id(self.instance)=}, {self._instantiated=}")
        self._instantiated = True
        self._args += list(args)
        self._kwargs |= kwargs

    def __repr__(self):
        return f"{self.__class__.__name__}(args={self._args}, kwargs={self._kwargs})"


a = Klass(1, x=2)
print(f"{a=}, {id(a)=}")
b = Klass(3, y=4, z=5)
print(f"{a=}, {id(a)=}")
print(f"{b=}, {id(b)=}, {(id(a) == id(b))=}")

"""
a=Klass(args=[1], kwargs={'x': 2}), id(a)=2649685241712
a=Klass(args=[1, 3], kwargs={'x': 2, 'y': 4, 'z': 5}), id(a)=2649685241712
b=Klass(args=[1, 3], kwargs={'x': 2, 'y': 4, 'z': 5}), id(b)=2649685241712, (id(a) == id(b))=True
"""

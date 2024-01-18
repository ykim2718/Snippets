"""
y, python singleton class - metaclass.py, 2019.1.25; 2021.10.17; 2024.1.18
https://github.com/ksu3101/TIL/blob/master/PythonDjango/170227.md
"""


class BaseClass:
	pass


class Singleton(type):
	_instances = {}

	def __call__(cls, *args, **kwargs):
		if cls not in cls._instances:
			cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
		return cls._instances[cls]


class Klass(BaseClass, metaclass=Singleton):

	_args = []
	_kwargs = dict()

	def __init__(self, *args, **kwargs):
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
a=Klass(args=[1], kwargs={'x': 2}), id(a)=2657314942832
a=Klass(args=[1], kwargs={'x': 2}), id(a)=2657314942832
b=Klass(args=[1], kwargs={'x': 2}), id(b)=2657314942832, (id(a) == id(b))=True
# FIXME 2024.1.18 ??? args=[1, 3], kwargs={'x': 2, 'y': 4, 'z': 5}
"""

"""
y, python class - singleton.py, 2019.1.25: 2021.10.17
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


class MainClass(BaseClass, metaclass=Singleton):
	pass


instance = MainClass()
print(instance, id(instance))
instance = MainClass()
print(instance, id(instance))

"""
y, python class - singleton (3).py, 2021.10.17
https://github.com/ksu3101/TIL/blob/master/PythonDjango/170227.md
"""


class BaseClass:
    pass


class MainClass:

    _instance = BaseClass()

    @property
    def instance(self):
        return MainClass._instance


instance = MainClass().instance
print(instance, id(instance))
instance = MainClass().instance
print(instance, id(instance))

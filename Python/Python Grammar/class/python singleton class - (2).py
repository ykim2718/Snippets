"""
y, python class - singleton (2).py, 2021.10.17
"""


class BaseClass:
    pass


class Singleton(type):
    _instance = BaseClass()
    print('main', id(_instance))

    def __call__(self, *args, **kwargs):
        print('call', id(Singleton._instance))
        return Singleton._instance


class MainClass(BaseClass, metaclass=Singleton):
    pass


instance = MainClass()
print(instance, id(instance))
instance = MainClass()
print(instance, id(instance))

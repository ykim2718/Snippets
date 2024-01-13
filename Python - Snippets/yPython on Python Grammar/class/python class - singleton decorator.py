"""
y, 2024.1.12 - 13
python class - singleton decorator.py
https://igeorgiev.eu/python/design-patterns/python-singleton-pattern-decorator/
"""

from functools import wraps
import pandas as pd
import time


def singleton(orig_cls):
    orig_new = orig_cls.__new__
    instance = None

    @wraps(orig_cls.__new__)
    def __new__(cls, *args, **kwargs):
        nonlocal instance
        if instance is None:
            # 2024.1.13 # instance = orig_new(cls, *args, **kwargs)
            instance = orig_new(cls)
            instance._is_created = True
        else:
            instance._is_created = False
        return instance

    orig_cls.__new__ = __new__
    return orig_cls


@singleton
class Klass:
    def __init__(self, x, y=0):
        print('self.__init__()', pd.Timestamp.now(), f"{self._is_created=}")
        if self._is_created:
            self._is_the_first = False
            self.timestamp = pd.Timestamp.now()
            self.x = x
            self.y = y


a = Klass(1, y=2)
print(f"{a.timestamp=}, {a.x=}, {a.y=}, {id(a.x)=}")
time.sleep(1.234)
b = Klass(x=2)
print(f"{id(a)=}, {id(b)=}, {(a == b)=}, {id(a.x)=}")
# assert a == b
print(f"{a.timestamp=}, {a.x=}, {a.y=}")
print(f"{b.timestamp=}, {b.x=}, {b.y=}")

"""
self.__init__() 2024-01-13 22:42:22.093439 self._is_created=True
a.timestamp=Timestamp('2024-01-13 22:42:22.093439'), a.x=1, a.y=2, id(a.x)=2271344027952
self.__init__() 2024-01-13 22:42:23.296761 self._is_created=False
id(a)=2271352728592, id(b)=2271352728592, (a == b)=True, id(a.x)=2271344027984
a.timestamp=Timestamp('2024-01-13 22:42:22.093439'), a.x=1, a.y=2
b.timestamp=Timestamp('2024-01-13 22:42:22.093439'), b.x=1, b.y=2
"""
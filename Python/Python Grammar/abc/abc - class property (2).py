"""
y, 2025.10.5
abc - class property (2).py
"""

import abc


class HookMeta(type):
    def __init__(cls, name, bases, namespace):
        super().__init__(name, bases, namespace)
        print(f"{name=} {bases=}")
        if bases:  # Avoid triggering on the base class itself
            print(f"{name=} {bases=} {namespace=}")
            # TODO 2025.10.5, Don't know how to find property method at the KLass class !!!


class MetaCombined(abc.ABCMeta, HookMeta):
    pass


class Klass(metaclass=MetaCombined):

    @property
    @abc.abstractmethod
    def value(self):
        pass


class Glass(Klass):

    @property
    def value(self):
        return 20251005


g = Glass()
print(f"{g.value=}")

"""
y, 2025.10.5
abc - class property.py
"""

import abc


class Klass(metaclass=abc.ABCMeta):

    @property
    @abc.abstractmethod
    def value(self):
        pass


class Glass(Klass):

    # @property
    def value(self):
        return 20251005


g = Glass()
print(f"{g.value=}")

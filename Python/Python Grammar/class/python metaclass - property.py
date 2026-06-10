"""
y, python metaclass - property.py, 2018.4.24
"""

import abc

class Klass(metaclass=abc.ABCMeta):

    @property
    @abc.abstractmethod
    def full_name(self):
        return self._full_name

    @full_name.setter
    @abc.abstractmethod
    def full_name(self, value):
        assert isinstance(value, str)
        self._full_name = value


class Glass(Klass):

    full_name = 'full name'
    pass


a = Glass()
a.full_name = 3
print(a.full_name)

"""
y, Python meta class - init.py, 2019.5.14
"""

import abc


class Glass(metaclass=abc.ABCMeta):

    @abc.abstractmethod
    def __init__(self):

        print(hasattr(self, 'k'), self.k)


class Klass(Glass):

    k = 'Klass'

    def __init__(self):

        super().__init__()


a = Klass()
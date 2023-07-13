"""
y, 2023.7.13
python abc - abstract property.py
https://stackoverflow.com/questions/5960337/how-to-create-abstract-properties-in-python-abstract-classes
https://docs.python.org/3/library/abc.html#abc.abstractproperty
"""


import abc


# class Glass(metaclass=abc.ABCMeta):
class Glass(abc.ABC):
    @property  # TODO 2023.7.13, DO NOT CHECK IF THE FUNCTION IS PROPERTY IN THE CHILD CLASS !!!
    @abc.abstractmethod
    def my_abstract_property(self):
        return 1


class Klass(Glass):

    def my_abstract_property(self):
        return 2


print(f"{Klass().my_abstract_property=}")


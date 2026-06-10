"""
y, 2016.9.27, Python class - overrode method.py
"""
class SuperClass():
    a = 'super'

    def print(self):
        print(self.a, 'in', self.__class__.__name__)

class SubClass(SuperClass):
    b = 'sub'

    """
    def print(self):
        print(self.b, self.__class__)
        super().print()
    """

sup = SuperClass()
sup.print()
sub = SubClass()
sub.print()

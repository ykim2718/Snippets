"""
y, Python - class as global.py, 2016.6.23
"""


class AClass():
    a = 1

    def print(self, arg):
        print(arg)


print(AClass.a)
a_class = AClass()
AClass.print(a_class, 'a')

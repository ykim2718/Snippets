"""
y, python class - __new__.py, 2019.9.12
https://corikachu.github.io/articles/python/python-magic-method
https://www.geeksforgeeks.org/dunder-magic-methods-python/
"""


class Klass:

    def __new__(self, *args, **kwargs):

        if len(args) == 0:
            return None
        else:
            print(args, kwargs, '<<< in Klass.__new__()')
            return super().__new__(self)

    def __init__(self, x=None):
        self.x = x


g = Klass()
print(type(g))

g = Klass(3)
print(type(g), g.x)
"""
y, python class - how to add property dynamically.py, 2019.7.15
"""


class Foo:
    pass


foo = Foo()
foo.a = 3
Foo.b = property(lambda self: self.a + 1)
print(foo.b)
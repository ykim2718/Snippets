"""
y, Python - super.py, 2016.6.13
http://stackoverflow.com/questions/4300738/python-which-is-the-better-way-of-calling-superclass-method
"""


class Foo(object):
    def display(self):
        print("In Foo")


class Foo2(Foo):
    def display(self):
        print("In Foo2")
        super(Foo2, self).display()
        print("Back in Foo2")


class Bar(Foo):
    def display(self):
        print("In Bar")
        super(Bar, self).display()
        print("Back in Bar")


class FooBar(Foo2, Bar):
    pass


FooBar().display()
print(FooBar.__mro__)

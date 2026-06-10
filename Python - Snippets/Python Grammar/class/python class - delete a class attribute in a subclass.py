"""
y, python class - delete a class attribute in a subclass, py, 2019.2.15
https://stackoverflow.com/questions/6057130/python-deleting-a-class-attribute-in-a-subclass
"""


class A:
    x = 5


class B(A):

    x = None

b = B()
print(b.x, hasattr(b, 'x'))
"""
y, 2016.6.30, Python - class method called outside.py
"""


class AClass:
    def a(self):
        print('id self', id(self))


a_class = AClass()
b = a_class.a
print(type(b), b.__code__.co_name, b.__code__.co_argcount)
b()
print('id class', id(a_class))

b_class = AClass()
b = b_class.a
b()
print('id class', id(b_class))

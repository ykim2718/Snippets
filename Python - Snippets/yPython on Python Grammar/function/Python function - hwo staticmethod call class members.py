"""
y, Python function - hwo staticmethod call class members.py, 2017.9.11
"""

class Klass:

    a = 1

    def class_method(self):
        print('class_method()')

    @staticmethod
    def one_static_method():
        Klass.another_static_method()
        Klass.class_method(None)
        print(Klass.a)

    @staticmethod
    def another_static_method():
        print("another_static_method()")

t = Klass()
t.a = 2
t.one_static_method()
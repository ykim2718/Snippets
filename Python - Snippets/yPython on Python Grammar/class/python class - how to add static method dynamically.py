"""
y, 2023.5.2
python class - how to add static method dynamically.py
"""


def f1(a):
    print(f"f1={a}")


def f2(a):
    print(f"f2={a}")


class Klass:

    def __init__(self, f):
        assert callable(f)
        # setattr(self.__class__, 'hello', classmethod(f))
        # self.hello = classmethod(f)  # >> TypeError: 'classmethod' object is not callable
        # setattr(self, 'hello', classmethod(f))  # >> TypeError: 'classmethod' object is not callable
        self.hello = f


k = Klass(f1)
k.hello('1st')

q = Klass(f2)
q.hello('2nd')
k.hello('3rd')

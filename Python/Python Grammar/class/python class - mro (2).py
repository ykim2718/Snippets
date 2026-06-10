"""
y, 2020.2.21
python class - mro (2).py
"""


class A:
    def out(self):
        print(f"class={self.__class__.__name__} >> A")


class B:
    def out(self):
        print(f"class={self.__class__.__name__} >> B")


class C(B, A):
    pass


import functools


class D(B, A):
    def __init__(self):
        self.out = functools.partial(A.out, self)


print(C.__mro__)  # method resolution order
C().out()
D().out()

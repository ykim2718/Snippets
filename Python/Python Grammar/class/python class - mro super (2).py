"""
y, 2022.7.19
python class - mro super (2).py
method resolution order (mro)
"""


class A:
    def __init__(self, a):
        self.a = a


class B:
    def __init__(self, b):
        self.b = b


class C(A, B):
    def __init__(self, a, b):
        case = 3
        if case == 1:  # working
            A.__init__(self, a)
            B.__init__(self, b)
        elif case == 2:  # working
            super().__init__(a)  # super(C, self).__init__(a)
            B.__init__(self, b)
        elif case == 3:
            super(A, self).__init__(a)  # error
            super(B, self).__init__(b)  # error
        else:
            raise NotImplemented


print(C.__mro__)  # method resolution order
print(f"{C(1, 2).a=}")
print(f"{C(1, 2).b=}")

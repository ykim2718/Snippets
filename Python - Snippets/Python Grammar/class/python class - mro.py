"""
y, 2023.10.23
python class - mro (1).py
"""


class A:
    def __init__(self):
        self.a = 1
        print('A', f"{vars(self)=}")


class B:
    def __init__(self):
        self.b = 1
        print('B', f"{vars(self)=}")


class C(A, B):
    def __init__(self):
        # super().__init__()  # A
        # super(A, self).__init__()  # B >> ????
        # super(B, self).__init__()  # not work
        # super(C, self).__init__()  # A
        A.__init__(self)  # A
        B.__init__(self)  # B


print(C.__mro__)
c = C()

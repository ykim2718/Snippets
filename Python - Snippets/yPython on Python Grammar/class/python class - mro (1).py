"""
y, python class - mro (1).py, 2018.12.28
    2019.2.2
https://docs.python.org/3/library/functions.html#super
https://rhettinger.wordpress.com/2011/05/26/super-considered-super/
https://stackoverflow.com/questions/9575409/calling-parent-class-init-with-multiple-inheritance-whats-the-right-way
"""

class A:

    start = 1

    def __init__(self):
        print('A')
        self.a = 2

    def add(self, x):
        return self.start + x

    def mul(self, x):
        return x * 10


class B:

    start = 2

    def __init__(self):
        print('B')
        self.b = 2

    def add(self, x):
        return self.start + x

    def mul(self, x):
        return x * 20


class C(A, B):

    def __init__(self):
        # super().__init__()  # same as super(C, self).__init__()
        # super(B, self).__init__()  # not work
        B.__init__(self)

    def add_using_A(self, x):
        return A.add(self, x)

    def add_using_B(self, x):
        return B.add(self, x)

    def mul_using_A(self, x):
        return A.mul(self, x)

    def mul_using_B(self, x):
        return B.mul(self, x)


print(C.__mro__)
c = C()
print(vars(c))
print(c.add_using_A(5))  # 6
print(c.add_using_B(5))  # 6   <<<  Not 7
print(c.mul_using_A(5))  # 50
print(c.mul_using_B(5))  # 100

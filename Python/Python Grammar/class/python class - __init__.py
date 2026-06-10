"""
y, python class - __init__.py, 2018.12.31
    2019.1.3
"""

print(__doc__)


class Klass:
    """~Klass~"""

    a = 1
    def __init__(self, b=2):
        self.b = b
        print(Klass.a, b)

    def other(self):
        self.c = 3

a = Klass()
a.other()
print('a.__dict__ =', a.__dict__)
print('a.__class__.__dict__ =', a.__class__.__dict__)

"""
y, python class - base vs instance attribute.py, 2019.1.3
"""

print(__doc__)


class Father:
    child = 1


class Sister(Father):
    pass


class Brother(Father):

    def __init__(self):
        self.child = 2

s = Sister()
b = Brother()
# b.child = 5
print(s.child, b.child, Father.child)  # 1 2 1

"""
y, Python - class counting instance.py, 2016.6.14
"""


class AClass:
    x = 0
    y = 0

    def __init__(self):
        AClass.x += 1
        self.y += 1


a = AClass()
print('x=', a.x)
print('y=', a.y)

b = AClass()
print('x=', a.x, b.x)
print('y=', a.y, b.y)

c = AClass()
print('x=', a.x, b.x, c.x)
print('y=', a.y, b.y, c.y)

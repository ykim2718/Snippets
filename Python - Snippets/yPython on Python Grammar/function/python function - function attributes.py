"""
y, python function - function attributes.py, 2019.9.14
"""

def foo():
    pass


setattr(foo, 'born', '12 Aug 1992')
print(getattr(foo, 'born'))
foo.name = 'Cara Delevingne'
print(foo.name)


def zoo(y):
    return zoo.x * y


zoo.x = 1
print(zoo(2))
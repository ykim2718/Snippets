"""
y, Python 3.0 - function annotation.py, 2018.2.28

https://www.python.org/dev/peps/pep-3107
"""

def foo(a: 'x', b: list, c: int = 9) -> max(2, 6):
    print(a, b, c)
    return a + b + c

print(foo(1, 2))
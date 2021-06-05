"""
y, python slice - ellipsis.py, 2019.11.14
"""

a = [..., 1, 2, 3]
b = [Ellipsis, 1, 2, 3]
print(a, b, len(a))


def foo():
    ...


class zoo:
    ...



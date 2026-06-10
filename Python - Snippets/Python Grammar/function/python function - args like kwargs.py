"""
y, python function - args like kwargs.py, 2019.1.3, 10.14
"""

print(__doc__)


def func(a, *, b=1, c):
    print(a, b, c)


func(1, b=2, c=3)
func(c=1, b=2, a=3)
func(a=1, c=1)

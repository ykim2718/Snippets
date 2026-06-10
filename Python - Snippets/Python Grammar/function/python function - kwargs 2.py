"""
y, python function - kwargs 2.py, 2019.1.3; 2023.7.13
"""

print(__doc__)


def func1(a=1, **kwargs):
    print('f1=', a)


def func2(a=1):
    print('f2=', a)


def func3(*, a=1, b):
    print('f3=', a, b)


kwargs = dict(a=3, b=3)

func1(**kwargs)
try:
    func2(**kwargs)
except TypeError as ex:
    print(ex)
func3(b=4)

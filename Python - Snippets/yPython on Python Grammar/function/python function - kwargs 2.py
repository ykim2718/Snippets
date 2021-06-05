"""
y, python function - kwargs 2.py, 2019.1.3
"""

print(__doc__)


def func1(a=1, **kwargs):
    print('f1=', a)


def func2(a=1):
    print('f2=', a)


kwargs = dict(a=3, b=3)

func1(**kwargs)
func2(**kwargs)
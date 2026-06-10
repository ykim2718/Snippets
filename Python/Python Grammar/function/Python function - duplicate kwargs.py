"""
y, Python function - duplicate kwargs.py, 2017.9.10
"""


def func(a=1, **kwargs):

    print(a, kwargs)


func(a=3, b=4)
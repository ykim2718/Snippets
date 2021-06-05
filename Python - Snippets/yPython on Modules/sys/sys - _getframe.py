"""
y, sys - _getframe.py, 2017.8.29

https://docs.python.org/3/library/sys.html

"""

import sys

def f1():
    f2()

def f2():
    f3()

def f3():
    for j in range(4):
        func_name = sys._getframe(j).f_code.co_name + '()'
        print(func_name)

f1()

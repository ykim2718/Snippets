"""
y, cgitb - detailed tracebacks.py, 2018.4.18

https://pymotw.com/2/cgitb/
"""

import cgitb
cgitb.enable(format='text')

def func1(arg1):
    local_var = arg1 * 2
    return func2(local_var)

def func2(arg2):
    local_var = arg2 + 2
    return func3(local_var)

def func3(arg3):
    local_var = arg2 / 2
    return local_var

func1(1)
"""
y, Python - hook exception.py, 2017.5.10

In Python, how do I print an error message without printing a traceback and
close the program when a condition is not met?
----------------------------------------------------------------------------
http://stackoverflow.com/questions/17784849/in-python-how-do-i-print-an-error-message-without-printing-a-traceback-and-clos


"""

import traceback
import sys


def excepthook(type, value, traceback_):
    print('excepthook()', type, value, traceback_)
    tb = traceback.format_tb(traceback_)[0] + type.__name__ + ': ' + str(value)
    print(tb)

sys.excepthook = excepthook

try:
    0/0
except:
    print('pass 0/0')

1/0
print('after 1/0')



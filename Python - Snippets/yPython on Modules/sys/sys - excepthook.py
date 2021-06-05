"""
y, 2020.5.7
sys - excepthook.py
"""

import sys
import traceback


def my_exception_hook(type, value, traceback_):

    if False:
        exception = ''.join(traceback.format_tb(traceback_) + [f"\n{type.__name__}: {value}"]).strip()
        print(exception, file=sys.stderr)
    else:
        traceback.print_last(file=sys.stderr)

if __name__ == '__main__':

    sys.excepthook = my_exception_hook

    0/0


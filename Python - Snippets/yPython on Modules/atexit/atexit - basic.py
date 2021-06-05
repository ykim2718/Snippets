"""
y, 2020.2.9
atexit - basic.py
"""

import atexit


@atexit.register
def my_exit():
    print('good bye ...')


if __name__ == '__main__':

    1/0
    print('end ...')
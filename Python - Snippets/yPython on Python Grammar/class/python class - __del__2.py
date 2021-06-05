"""
y, python class - __del__2.py, 2019.18
"""


class Klass:

    def __del__(self):
        print('__del__')


def a():

    k = Klass()
    print('before exit of function')


a()
print('after exit of function')



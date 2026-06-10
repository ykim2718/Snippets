"""
y, Python class - __del__.py, 2017.9.8
"""

import threading

class Klass:

    a = 1
    lock = None

    def __init__(self):

        self.lock = threading.Lock()

    def __del__(self):

        print('__del__')


klass = Klass()
del klass
print('done ...')


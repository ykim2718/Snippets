"""
y, 2016.5.15
http://jsonpickle.github.io/
http://stackoverflow.com/questions/2398078/saving-and-loading-objects-from-file-using-jsonpickle
"""

import jsonpickle


class A(object):
    def __init__(self, name):
        self.name = name


d = jsonpickle.decode(js)  # type is available
print(d, type(d))

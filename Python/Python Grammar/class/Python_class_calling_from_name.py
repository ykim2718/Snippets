"""
y, 2016.11.10, Python_class_calling_from_name.py

[Reference]
Python dynamic instantiation from string name of a class in dynamically imported module
    http://stackoverflow.com/questions/4821104/python-dynamic-instantiation-from-string-name-of-a-class-in-dynamically-imported
How do I call setattr() on the current module?
    http://stackoverflow.com/questions/2933470/how-do-i-call-setattr-on-the-current-module
"""
import importlib
import sys

class Glass():
    def print(self):
        print(self.__class__.__name__)

if __name__ == "__main__":

    print('before import')
    my_module = importlib.import_module("Python_class_calling_from_name")
    # my_module = __import__("Python_class_calling_from_name")
    print('after import')
    my_class = getattr(my_module, "Glass")
    my_class().print()

    this_module = sys.modules[__name__]
    my_class = getattr(this_module, "Glass")
    my_class().print()



"""
y, 2020.2.19
types - how to convert dict to class.py
"""

from types import SimpleNamespace

a_dict = dict(hello='world')
obj = SimpleNamespace(**a_dict)
print(obj)


class Klass:

    def __init__(self, **kwargs):
        ...

    def __repr__(self):
        return f"{__class__.__name__}({vars(self)})"


obj = Klass(**a_dict)  # not working, 2020.2.19
obj.a = 'a'
print(obj)

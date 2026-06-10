"""
y, 2019.9.12; 2024.6.19
python class - __new__.py
https://corikachu.github.io/articles/python/python-magic-method
https://www.geeksforgeeks.org/dunder-magic-methods-python/
"""


class Klass:

    def __new__(self, *args, **kwargs):
        print('called __new__()')
        if len(args) == 0:
            return None
        else:
            print(f"\t{args=}, {kwargs=}, <<< in Klass.__new__()")
            return super().__new__(self)

    def __init__(self, x=None):
        print('called __init__()')
        self.x = x


g = Klass()
print(f"\t{type(g)=}")

print('-' * 32)

g = Klass(3)
print(f"\t{type(g)=}, {g.x=}")
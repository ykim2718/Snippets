"""
y, generator - class.py, 2019.1.30
https://treyhunner.com/2018/06/how-to-make-an-iterator-in-python/
https://www.programiz.com/python-programming/methods/built-in/iter
"""

class Generator:

    def __init__(self, array):
        assert isinstance(array, list)
        self.array = array

    def __iter__(self):
        for a in self.array:
            yield a


G = iter(Generator([3, 2, 1, 0]))
print('next(G) =', next(G))
print('next(G) =', next(G))

for g in G:
    print('g=', g)


import inspect

print(inspect.iscoroutine(G))  # False
print(inspect.isgenerator(G))  # True
print(inspect.isgeneratorfunction(G))  # False

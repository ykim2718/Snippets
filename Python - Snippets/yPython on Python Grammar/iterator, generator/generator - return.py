"""
y, 2020.6.8
generator - return.py
"""


def test():

    yield 1
    yield 2
    return
    yield 3


for j in test():
    print(j)
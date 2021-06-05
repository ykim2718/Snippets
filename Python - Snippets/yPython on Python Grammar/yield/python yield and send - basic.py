"""
y, python yield and send - basic.py, 2017.12.6
"""

def gen1():
    yield 'one'
    yield 'two'
    yield 'three'

g = gen1()
print(next(g))
print(next(g))
print(next(g))
# print(next(g))

def gen2():
    val = 1
    while True:
        val = (yield val) * 2

g = gen2()
print(next(g))
print(g.send(2))
print(g.send(3))

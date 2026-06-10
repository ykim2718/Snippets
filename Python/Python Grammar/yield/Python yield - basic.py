"""
y, Python - yield.py, 2016.6.26, 10.26
"""
print("y, 2016.6.26 ")


def return_by_yield():
    yield 1
    yield 2
    yield 3


a, b, c = return_by_yield()
print(a, b, c)

d = return_by_yield()
print(d)
print(next(d))
print(next(d))

print("y, 2016.6.26 ")
a_list = (d for d in ['a', 'b', 'c'])
for j in range(5):
    print(j, next(a_list))

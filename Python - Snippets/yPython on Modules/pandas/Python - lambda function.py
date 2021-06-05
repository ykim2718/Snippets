"""
y, 2016.9.24, Python - lambda function.py
"""
def add(a, b):
    return a + b

def wrapper(func):
    return func(1, 2)

r = wrapper(add)
r = wrapper(lambda a, b: a + b)

print(r)

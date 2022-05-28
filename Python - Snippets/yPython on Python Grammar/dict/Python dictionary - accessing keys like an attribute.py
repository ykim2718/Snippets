"""
y, Python dictionary - accessing keys like an attribute.py, 2018.1.4

Accessing dict keys like an attribute?
https://stackoverflow.com/questions/4984647/accessing-dict-keys-like-an-attribute

"""

d = {'a': 1, 'b': 2}
C = type('type_C', (object,), d)
c = C()
print(dir(c))
print(vars(c))
print(c.a, c.b)

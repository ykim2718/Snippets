"""
y, 2016.7.7, Python - class setattr getattr.py
"""


class AClass:
    a = 1
    b = None
    c = [3]

    def d(self):
        pass


a_class = AClass()

print(a_class.a, type(a_class.a), a_class.b, type(a_class.b), a_class.c, type(a_class.c))

attributes = AClass.__dict__.keys()
for name in ['a', 'b']:
    if name not in attributes: continue
    attr = getattr(AClass, name)
    if attr is None: continue
    setattr(a_class, name, str(attr))

print(a_class.a, type(a_class.a), a_class.b, type(a_class.b), a_class.c, type(a_class.c))

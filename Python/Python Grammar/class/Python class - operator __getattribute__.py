"""
y, Python class - operator __getattribute__.py, 2017.9.7
"""

class Klass:

    a = 0

    def __getattr__(self, item):
        print('__getattr__')
        return super().__getattr__(item)

    def __getattribute__(self, item):
        if item == 'a':
            print('__getattribute__', item)
        return super().__getattribute__(item)

k = Klass()
print(dir(k))
print(k.__dict__, k.a)
k.b = 1
print(k.__dict__, k.b)
k.a = 10  # no call of __getattribute__()


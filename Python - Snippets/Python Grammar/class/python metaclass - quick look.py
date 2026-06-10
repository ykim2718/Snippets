"""
y, Python metaclass - quick look.py, 2017.5.7

https://blog.ionelmc.ro/2015/02/09/understanding-python-metaclasses/

"""

MyClass = type('MyClass', (), {})

print(MyClass)


class Funky():
    def __call__(self):
        print("Look at me, I work like a function!")

f = Funky()
print(type(f))
f()
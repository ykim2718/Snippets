"""
y, Python - class attributes.py, 2016.6.15, 9.2
looping over all member variables of a class in python
http://stackoverflow.com/questions/1398022/looping-over-all-member-variables-of-a-class-in-python
+
Y
"""


class AClass:
    a = 0
    b = 0
    col_a = 'col_a'

    def call(self):
        pass

    def dir_self(self):
        attrs = dir(self)
        print([h for h in dir(self) if h.startswith('col_')])


a_class = AClass()
a_class.dir_self()

print('Class attribute list')
print(dir(a_class))
print(vars(a_class))

print()
print('Class attributes and type, callable')
for attr in dir(AClass()):
    print(attr, type(attr), callable(getattr(AClass(), attr)))

print()
print('Class variables not starting with double underscore')
for attr in dir(AClass()):
    if not attr.startswith('__'):
        print(attr)

"""
y, 2016.6.12
"""


class AClass:
    x = 1


print('id(AClass)=', id(AClass))
AClass.x = 2

a = AClass()
b = AClass()
print('id(a), id(a.__class__)=', id(a), id(a.__class__))
print('id(b), id(b.__class__)=', id(b), id(b.__class__))
print(a.x, b.x)

AClass.x = 3
c = AClass()

print(a.x, b.x, c.x)

"""
id(AClass)= 35359408
id(a), id(a.__class__)= 35080176 35359408
id(b), id(b.__class__)= 35080144 35359408
2 2
3 3 3
"""

a.x = 1
print(a.x, b.x, c.x)

"""
1 3 3
"""

a.__class__.x = 2
print(a.x, b.x, c.x)

"""
1 2 2
"""

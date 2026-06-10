"""
y, Python class - property.py, 2019.6.11
"""


class Base:

     b = 1


class Offspring(Base):

     c = 2

     @property
     def b(self):

         return self.c


print(Base.b)
print(Offspring.b)


g = Offspring()
print(g.b, type(g.b), type(g).b, isinstance(type(g).b, property))
print(g.__class__.b, type(g).b)


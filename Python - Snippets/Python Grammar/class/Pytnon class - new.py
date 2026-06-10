"""
y, Pytnon - class new.py, 2016.6.15
"""


class CClass:
    c = 0


class AClass:
    a = 1

    def __init__(self):
        CClass.c += 1

    def print(self):
        print(self.__class__.__name__, self.a)


a_list = []
for i in range(3):
    new_class = type('New_class_' + str(i), (AClass,), {})
    cls = new_class()
    # cls.a = i
    a_list.append(cls)

for i in range(len(a_list)):
    print(a_list[i].__class__.__name__, a_list[i].a)
    # a_list[i].print()

AClass.a = 99  # Note, it's working only if AClass.a has never been assigned

for i in range(len(a_list)):
    a_list[i].print()

print(AClass.a, CClass.c)

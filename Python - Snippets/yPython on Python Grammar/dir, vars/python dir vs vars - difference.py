"""
y, python dir vs vars - difference.py, 2019.6.3
"""

class Mother:

    m = 1


class Child(Mother):

    c = 2


a = Child()

print(vars(a))
print(dir(a))

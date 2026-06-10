"""
y, python class - name.py, 2018.12.27
"""

class Klass:

    def __init__(self):
        self.name = self.__class__.__name__
    pass

a = Klass()
print(a.name)
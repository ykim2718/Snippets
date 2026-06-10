"""
y, python class - staticmethod.py, 2018.12.28
"""

class Klass:

    name = 'Klass ...'

    @staticmethod
    def print():
        print(Klass.name)

a = Klass()
a.print()

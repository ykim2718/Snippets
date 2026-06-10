"""
y, 2016.7.28, Python - class method overriding.py
"""


class Mother():
    def talk(self):
        print('Mother said love yourself')

    def call(self):
        self.talk()


class Son(Mother):
    def talk(self, to='mother'):
        print('keep trying harder to myself, %s' % to)


a = Son()
a.call()

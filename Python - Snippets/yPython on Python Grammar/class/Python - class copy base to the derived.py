"""
y, PythonClassCopyBaseToTheDerived.py, 2016.5.26
http://stackoverflow.com/questions/21699707/python-how-to-copy-all-attibutes-from-base-class-to-derived-one
"""


class SuperHero(object):
    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name


class SuperMan(SuperHero):
    def __init__(self, source=None):
        if source is not None:
            self.__dict__.update(source.__dict__)


sh = SuperHero()
sh.setName("Clark Kent")
sm = SuperMan(sh)
print(sm.getName())

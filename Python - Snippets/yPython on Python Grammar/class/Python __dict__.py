"""
y, 2016.10.16
http://stackoverflow.com/questions/19564186/dir-and-help-not-showing-all-attributes-of-an-object-in-python
"""
class Const(object):
    def __init__(self, val):
        self.value = val
    def __getattr__(self, a):
        return self.value
    def __setattr__(self, a, v):
        self.__dict__[a] = v

c = Const(1)
print(dir(c))
print('dict >>>', c.__dict__)
print(c.some_strange_attribute_name)
print('dict >>>', c.__dict__)
c.some_strange_attribute_name = 2
print(c.some_strange_attribute_name)
print('dict >>>', c.__dict__)

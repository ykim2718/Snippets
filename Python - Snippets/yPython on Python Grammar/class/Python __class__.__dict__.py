"""
y, Python __class__.__dict__.py, 2016.10.17, 2019.6.11
"""


class AClass():

    a = 1  # saved at __class__.__dict__
    b = 2  # saved at __class__.__dict__


class BClass(AClass):

    a = 10  # saved at __class__.__dict__

    def __init__(self):

        self.b = 20  # saved at __dict__

    def print(self):

        print(self.__class__.__dict__)
        print(self.__dir__())
        print(dir(self))
        print(vars(self))

B = BClass()
B.print()


print(B.__dict__)  # not include 'a', but 'b'
print(B.__class__.__dict__, id(B.__class__.__dict__))  # include 'a', not 'b'
print(BClass.__dict__, id(BClass.__dict__))  # same as B.__class__
print(type(B).__dict__, id(type(B).__dict__))  # same as B.__class__

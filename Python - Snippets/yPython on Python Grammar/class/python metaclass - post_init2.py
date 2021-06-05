"""
y, python metaclass - post_init.py, 2018.4.24
https://stackoverflow.com/questions/16017397/injecting-function-call-after-init-with-decorator
https://stackoverflow.com/questions/11276037/python-3-typeerror-metaclass-conflict-the-metaclass-of-a-derived-class-must-b
"""

"""
class M_A(type): pass
class M_B(type): pass
class A(metaclass=M_A): pass
class B(metaclass=M_B): pass

class M_C(M_A, M_B): pass
class C(A, B, metaclass=M_C): pass

c = C()
print(type(c))

"""

# raise UserWarning("Not working ....")

import abc


def __call__(cls, *args, **kwargs):

    obj = type.__call__(cls, *args, **kwargs)
    obj.post_init()
    return obj

class Glass(type):

    def __call__(cls, *args, **kwargs):

        obj = type.__call__(cls, *args, **kwargs)
        obj.post_init()
        return obj

    def __new__(cls, *args, **kwargs):
        print('Glasssss', cls)
        return type('aaa', (), {'__call__': __call__})
        # return super().__new__(cls, *args, **kwargs)
        # return super().__new__(cls) # , 'aaa', (), {})

# class Glass(metaclass=Glass_): pass

class Klass(Glass, metaclass=abc.ABCMeta):

    @abc.abstractmethod
    def post_init(self):
        pass

# class Alass(Glass, Klass): pass

class Foo(Glass):

    def __init__(self):
        print("__init__")

    def post_init(self):
        print("post_init")


a = Foo()
# a()

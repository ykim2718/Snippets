"""
y, python metaclass - post_init.py, 2018.4.24
https://stackoverflow.com/questions/16017397/injecting-function-call-after-init-with-decorator
"""

class PostInitCaller(type):

    def __call__(cls, *args, **kwargs):

        obj = type.__call__(cls, *args, **kwargs)
        obj.post_init()
        return obj

class Foo(object, metaclass=PostInitCaller):

    def __init__(self):
        print("__init__")

    def post_init(self):
        print("post_init")


class Bar(Foo):
    pass

a = Foo()
b = Bar()
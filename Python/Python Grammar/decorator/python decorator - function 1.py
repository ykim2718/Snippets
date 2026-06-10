"""
y, python decorator - function1.py, 2015.5.25
"""


class MyFuncDecorator:
    func = None

    def __init__(self, func):
        # print(func.__name__, "added")
        self.func = func

    def __call__(self, *args, **kwargs):
        print('start .. ', self.func.__name__)
        self.func(*args, **kwargs)
        print('end ..', self.func.__name__)


@MyFuncDecorator
def hello(name):
    print("Hello %s !" % name)


@MyFuncDecorator
def goodbye(name):
    print("Goodbye %s !" % name)


hello('world')
hello('dd')

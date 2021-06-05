"""
y, 2016.8.8, Python - function - inspect argument.py
"""
import inspect


def a(b, c='c', *, d=None):
    print(b, c)


def b(b, c='c', d=None, *arg, e=None):
    pass


def investigate(f):
    print('function name:', f.__code__.co_name)
    print(f.__code__.co_names)
    print(f.__code__.co_argcount)
    print(f.__defaults__, len(f.__defaults__))
    print(f.__kwdefaults__, len(f.__kwdefaults__))
    print(inspect.getfullargspec(f))
    print('arg count =', f.__code__.co_argcount - len(f.__defaults__))
    print('kwarg count =', len(f.__defaults__))


investigate(a)
investigate(b)

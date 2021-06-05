"""
y, python class - assign to __init__.py, 2019.11.20
"""


class Klass:

    def __init__(self, a, *args, b=2, **kwargs):
        print(a, args)
        print(b, kwargs)

    print(__init__.__dict__)
    import inspect
    fas = inspect.getfullargspec(__init__)
    __init__.__dict__['args'] = fas.args
    __init__.__dict__['kwargs'] = fas.kwonlyargs
    print(__init__.__dict__)

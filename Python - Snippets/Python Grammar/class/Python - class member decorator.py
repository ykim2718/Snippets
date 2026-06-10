"""
y, Python - class member decorator, 2016.12.14
"""

def decorator(fn):

    def decorated(self, *args, **kwargs):
        if self.a:
            return fn(self, *args, **kwargs)
        else:
            return

    return decorated


class Glass():

    a = 0

    @decorator
    def test(self, *args, **kwargs):
        print('test', args, kwargs)


a = Glass()
a.a = 1
a.test(123, b='b')

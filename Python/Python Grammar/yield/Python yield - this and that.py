"""
y, 2016.10.23, yield this and that.py
"""
def that():
    while True:
        j = yield
        print('that', j)


def this(j, that):
    while True:
        j += 1
        print('this', j)
        that.send(j)
        yield  # do once and wait another next() at here


t = that()
next(t)  # start generator and wait for input via yield
s = this(0, t)
next(s)
next(s)

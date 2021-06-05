"""
y, 2016.10.23, yield hello world.py
http://soooprmx.com/wp/archives/5622
"""
def coroutine(func):
    def start(*args, **kwargs):
        cr = func(*args, **kwargs)
        cr.next()
        return cr
    return start

@coroutine
def printer():
    print("Open a new printer")
    try:
        while True:
            line = (yield)
            print(line)
    except GeneratorExit:
        print("Closing...")

prn = printer()

prn = printer()
prn.send('hello world')

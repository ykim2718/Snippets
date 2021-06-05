"""
y, 2016.10.27, yield from basic.py
"""
def chain(*iters):
    for it in iters:
        yield from it

a = chain(iter('node'))
print(next(a))
for b in a:
    print(b)

def chain2(iterable):
    yield from iter(iterable)

a = chain2('.js')
for b in a:
    print(b)
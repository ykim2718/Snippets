"""
y, Python yield - enumeratex.py, 2017.5.27

"""

def enumeratex(iterable, start=0, step=1):

    j = start
    for k in iterable[start::step]:
        yield j, k
        j += step

a = [x for x in range(16)]

for j, x in enumeratex(a, start=2, step=2):
    print(j, x)
    a[j] = x * 10

print(a)
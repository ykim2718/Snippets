"""
y, 2021.12.18 (Somerled)
generator - yield from.py.
"""


def test1():
    a = [(1, 10), (2, 20)]
    for j, k in a:
        yield j, k


def test2(return_both=True):

    if return_both:
        yield from test1()
    else:
        # yield from test1()[0]  # TypeError: 'generator' object is not subscriptable
        for r in test1():
            yield r[0]


for r in test2():
    print(r)

for r in test2(return_both=False):
    print(r)


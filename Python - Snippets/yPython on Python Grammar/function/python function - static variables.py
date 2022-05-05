"""
y, 2022.4.25, 5.5
python function - static variables.py
"""


def f(_flags=[0]*3):
    print(f"{_flags=}")
    _flags[0] += 1
    if _flags[0] > 1:
        _flags[1] += 1
        _flags[2] = 'one'


f()
f()
f()


def g():
    if hasattr(g, '_counter'):
        g._counter += 1
    else:
        setattr(g, '_counter', 0)
    print(f"{g._counter=}")
g()  # g._counter=0
g()  # g._counter=1

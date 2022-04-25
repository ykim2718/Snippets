"""
y, 2022.4.25
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

"""
y, Python dictionary - shallow copy.py, 2017.12.18
"""

from copy import deepcopy

for j in ['assign', 'shallowcopy', 'deepcopy']:

    a = {1: 'a', 2: 'b', 3: [4, 5]}
    print(j, a)
    if j == 'assign':
        b = a
    elif j == 'shallowcopy':
        b = a.copy()
    elif j == 'deepcopy':
        b = deepcopy(a)
    b[1] = 1
    b[3].append(6)
    b[7] = 7
    b.pop(2)
    print(j, a, b)

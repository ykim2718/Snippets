"""
y, 2022.5.3
divmod - basic.py
"""

divider = 3
for j in range(9):
    print(j//divider, j%divider, divmod(j, divider))

"""
0 0 (0, 0)
0 1 (0, 1)
0 2 (0, 2)
1 0 (1, 0)
1 1 (1, 1)
1 2 (1, 2)
2 0 (2, 0)
2 1 (2, 1)
2 2 (2, 2)
"""
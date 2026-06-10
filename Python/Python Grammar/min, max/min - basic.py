"""
y, 2022.5.11
min - basic.py
"""

a = [(1, 1), (5, 2), (4, 3), (3, 4), (2, 5), (1, 6)]
ll = 3
x = min(a, key=lambda t: (t[0], t[1]) if t[1] >= ll else (999, 0))
print(x)  # (1, 6)

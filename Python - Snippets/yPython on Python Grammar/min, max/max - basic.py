"""
y, 2022.5.2
max - basic.py
"""

x = max(range(1, 7), key=lambda v: 0 if v in (5, 6) else v)  # 1 2 3 4 5 6
print(x)  # 4

"""
y, 2022.5.2
max - basic.py
"""

a = max(range(1, 7), key=lambda x: 0 if x in (5, 6) else x)  # 1 2 3 4 5 6
print(a)  # 4

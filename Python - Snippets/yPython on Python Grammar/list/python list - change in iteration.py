"""
y, 2025.4.25
python list - change in iteration.py
"""

a = [1, 2, 3]
for j, v in enumerate(a):
    if v == 2:
        a[j] = 20

print(f"{a=}")  # a=[1, 20, 3]

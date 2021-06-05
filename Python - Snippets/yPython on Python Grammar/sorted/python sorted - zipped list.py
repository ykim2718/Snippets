"""
y, python sorted - zipped list.py, 2018.12.8
"""

a = [1, 2, 3]
b = [3, 2, 1]
c = sorted(zip(a, b), key=lambda x: x[1])
print(c)

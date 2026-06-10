"""
y, python list - assign in for loop.py, 2017.9.27
"""

a = list(range(5))
print(a)
for j, e in enumerate(a):
    a[j] = j * 10
print(a)

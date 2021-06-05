"""
y, python list - interleaved list.py, 2018.5.7, 11.20
"""

a = [1, 2, 3]
b = [4, 5, 6, 7]
interleaved = [each for pair in zip(a, b) for each in pair]
print(interleaved)  # [1, 4, 2, 5, 3, 6]

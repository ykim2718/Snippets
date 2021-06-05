"""
y, numpy - copy.py, 2019.9.15
"""


import numpy as np

a = np.zeros((2, 3, 4))
print(a)

b = np.ones((2, 3))
print(b)

a[:, :, 1] = b
a[:, :, 2] = b * 2
print(a)

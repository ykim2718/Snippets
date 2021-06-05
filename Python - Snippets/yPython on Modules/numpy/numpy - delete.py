"""
y, numpy - delete.py, 2018.12.31
https://docs.scipy.org/doc/numpy-1.15.1/reference/generated/numpy.delete.html
"""

import numpy as np

arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]])
print(arr)
print(np.delete(arr, 1, axis=0))  # delete row
print(np.delete(arr, np.s_[::2], axis=1))  # delete column
print(np.delete(arr, [0, 2], axis=1))  # delete column
print(np.delete(arr, [1, 3, 5], None))  # delete after making array flatten

"""
y, 2020.1.20
numpy - apply_along_axis.py
https://docs.scipy.org/doc/numpy/reference/generated/numpy.apply_along_axis.html
"""

import numpy as np


def my_func(a):
    return a[0] + a[1] + a[2]


a = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(a)
b = np.apply_along_axis(my_func, 0, a)
print(b)

"""
[[1 2 3]
 [4 5 6]
 [7 8 9]]
[12 15 18]
"""

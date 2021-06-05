"""
y, 2020.4.21
numpy - take.py
https://docs.scipy.org/doc/numpy/reference/generated/numpy.take.html
"""

import numpy as np

a = np.arange(24).reshape(4, 2, 3)
indices = np.array([[1, 2], [2, 3]])
b = np.take(a, indices)
print(f"a={a}, shape={a.shape}")
print(f"b={b}, shape={b.shape}")

"""
a=[[[ 0  1  2] [ 3  4  5]]
   [[ 6  7  8] [ 9 10 11]]
   [[12 13 14] [15 16 17]]
   [[18 19 20] [21 22 23]]], shape=(4, 2, 3)
b=[[1 2]
   [2 3]], shape=(2, 2)
"""

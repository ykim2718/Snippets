"""
y, 2020.4.21; 2023.4.21
numpy - take.py
https://docs.scipy.org/doc/numpy/reference/generated/numpy.take.html
"""

import numpy as np

a = np.arange(24).reshape(4, 2, 3)
print(f"a={a}, shape={a.shape}")
"""
a=[[[ 0  1  2] [ 3  4  5]]
   [[ 6  7  8] [ 9 10 11]]
   [[12 13 14] [15 16 17]]
   [[18 19 20] [21 22 23]]], shape=(4, 2, 3)
"""

print(f"{np.take(a, [2], axis=0).tolist()=}")
print(f"{np.take(a, [1, 2], axis=0).tolist()=}")
"""
[[[12, 13, 14], [15, 16, 17]]]]
[[[6, 7, 8], [9, 10, 11]], [[12, 13, 14], [15, 16, 17]]]
"""

print(f"{np.take(a, [1], axis=1).tolist()=}")
"""
[[[3, 4, 5]], [[9, 10, 11]], [[15, 16, 17]], [[21, 22, 23]]]
"""

print(f"{np.take(a, [1], axis=-1).tolist()=}")
"""
[[[1], [4]], [[7], [10]], [[13], [16]], [[19], [22]]]
"""


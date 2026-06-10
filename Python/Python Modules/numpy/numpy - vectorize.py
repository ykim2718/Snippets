"""
y, 2022.8.27
numpy - vectorize.py
"""

import numpy as np

a = np.arange(120).reshape((2, 3, 4, 5))
print(f"{a[0][0]=}")
print(f"{a.shape=}")  # a.shape=(2, 3, 4, 5)


def scale_to_0_1(s):  # s scalar
    assert np.issubdtype(int, np.integer)
    return s/10


vf = np.vectorize(scale_to_0_1)  # element-wise
b = vf(a)
print(f"{b[0][0]=}")

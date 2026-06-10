"""
y, numpy - savez and load.py, 2019.10.6
https://docs.scipy.org/doc/numpy/reference/generated/numpy.load.html
"""

import numpy as np

a = np.array([[1, 2, 3], [4, 5, 6]])
b = np.array([1, 2])
np.savez('numpy.npz', a=a, b=b)
data = np.load('numpy.npz')
print(f"a={data['a']}")  # array([[1, 2, 3], [4, 5, 6]])
print(f"b={data['b']}")  # array([1, 2])
data.close()

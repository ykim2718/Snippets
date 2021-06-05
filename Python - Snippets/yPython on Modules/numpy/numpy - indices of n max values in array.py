"""
y, numpy - indices of n max values in array.py, 2019.3.8
https://stackoverflow.com/questions/6910641/how-do-i-get-indices-of-n-maximum-values-in-a-numpy-array
"""

import numpy as np

a = np.array([4, 5, 3, 6, 2, 7, 1, 8])
n_biggest = 5
indices = (-a).argsort()[:n_biggest]
print(a)
print(indices)
print(a[indices])

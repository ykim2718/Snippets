"""
y, numpy - flip.py, 2019.11.14
https://docs.scipy.org/doc/numpy/reference/generated/numpy.flip.html
"""

import numpy as np

a = np.arange(24).reshape(2, 3, 4)
print(a, a.shape)
print(np.flip(a, 0), (np.flip(a, 0) == np.flipud(a)).all())
print(np.flip(a, 1), (np.flip(a, 1) == np.fliplr(a)).all(), (np.flip(a, 1) == a[:, ::-1, :]).all())
print(np.flip(a, 2))

"""
[[[ 0  1  2  3]
  [ 4  5  6  7]
  [ 8  9 10 11]]
 [[12 13 14 15]
  [16 17 18 19]
  [20 21 22 23]]] (2, 3, 4)
  
[[[12 13 14 15]
  [16 17 18 19]
  [20 21 22 23]]
 [[ 0  1  2  3]
  [ 4  5  6  7]
  [ 8  9 10 11]]] True
  
[[[ 8  9 10 11]
  [ 4  5  6  7]
  [ 0  1  2  3]]
 [[20 21 22 23]
  [16 17 18 19]
  [12 13 14 15]]] True True
  
[[[ 3  2  1  0]
  [ 7  6  5  4]
  [11 10  9  8]]
 [[15 14 13 12]
  [19 18 17 16]
  [23 22 21 20]]]
"""

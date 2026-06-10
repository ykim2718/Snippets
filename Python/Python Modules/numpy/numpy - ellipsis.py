"""
y, numpy - ellipsis.py, 2019.11.14
"""

import numpy as np

a = np.arange(16).reshape((2, 2, 2, 2))
print(a)
print(a[1, ..., 1])
print(a[1, :, :, 1])

"""
[[[[ 0  1]
   [ 2  3]]
  [[ 4  5]
   [ 6  7]]]
 [[[ 8  9]
   [10 11]]
  [[12 13]
   [14 15]]]]
   
[[ 9 11]
 [13 15]]
 
[[ 9 11]
 [13 15]]
"""

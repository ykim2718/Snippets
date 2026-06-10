"""
y, numpy - where (2).py, 2019.11.17
"""

import numpy as np

a = np.arange(5) * 2
print(a)
b = np.where(a > 4, a * 10, a)
print(b)
c = np.where(a > 4)
print(c)

"""
[0 2 4 6 8]
[ 0  2  4 60 80]
(array([3, 4], dtype=int64),)
"""
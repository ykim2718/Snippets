"""
y, numpy - shuffle.py, 2019.3.7
https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.shuffle.html
"""

import numpy as np

arr = np.arange(12).reshape((4, 3))
print(arr)
np.random.shuffle(arr)
print(arr)

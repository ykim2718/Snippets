"""
y, 2020.4.4 (Saturday Home)
numpy - how to do hands-on linear regression.py
http://science.clemson.edu/physics/labs/tutorials/excel/regression.html
https://www.tensorflow.org/api_docs/python/tf/linalg
"""

# GOAL: linear regression compatible to tf.linalg and tf.math APIs

import numpy as np

batch_size = 2
y = np.array([[1, 4, 3, 6, 5]])
y = np.tile(y, [batch_size, 1])
x = np.arange(y.shape[1])
x = np.tile(x, [y.shape[0], 1])
print(f"x={x}")  # x=[[0 1 2 3 4] [0 1 2 3 4]]
print(f"y={y}")  # y=[[1 4 3 6 5] [1 4 3 6 5]]
print(f"x.shape={x.shape}, y.shape={y.shape}")  # x.shape=(2, 5), y.shape=(2, 5)

n = x.shape[1]
sx = np.sum(x, axis=1)  # Sx
sy = np.sum(y, axis=1)  # Sy
sxy = np.sum(x * y, axis=1)
sxx = np.sum(x ** 2, axis=1)  # Sx^2, Sum of squares of x
syy = np.sum(y ** 2, axis=1)  # Sy^2, Sum of squares of y
ssx = sx ** 2  # (Sx)^2, Square of sum of x
ssy = sy ** 2  # (Sy)^2, Square of sum of y
print(f"n={n}, sx={sx}, sy={sy}, sxy={sxy}, sxx={sxx}, syy={syy}, ssx={ssx}, ssy={ssy}")  # see below
# + n=5, sx=[10 10], sy=[19 19], sxy=[48 48], sxx=[30 30], syy=[87 87], ssx=[100 100], ssy=[361 361]

dividend = n*sxy-sx*sy
slope = dividend/(n*sxx-ssx)
yi = (sy-slope*sx)/n
r = dividend/np.sqrt((n*sxx-ssx)*(n*syy-ssy))
print(f"slope={slope}, yi={yi}, r2={r**2}")  # slope=[1. 1.], yi=[1.8 1.8], r2=[0.67567568 0.67567568]  << correct

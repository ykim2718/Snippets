"""
y, 2021.12.13
numpy - r or r2.py
https://www.kite.com/python/answers/how-to-calculate-r-squared-with-numpy-in-python
https://numpy.org/doc/stable/reference/generated/numpy.corrcoef.html  >> Pearson product-moment correlation cofficients.
"""

import numpy as np

x = [1, 2, 3]
y = [3, 2, 1]
correlation_matrix = np.corrcoef(x, y)
correlation_xy = correlation_matrix[0, 1]
print(correlation_xy)
r_squared = correlation_xy**2
print(r_squared)

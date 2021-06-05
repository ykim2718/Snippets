"""
y, sklearn - polynomialfeatures.py, 2019.12.26
"""

import numpy as np
from sklearn.preprocessing import PolynomialFeatures

X = np.arange(6).reshape(3, 2)
print(X)
poly = PolynomialFeatures(degree=2, interaction_only=False, include_bias=False)
X = poly.fit_transform(X)
print(X)

'''
[[0 1]
 [2 3]
 [4 5]]
[[ 1.  0.  1.  0.  0.  1.]
 [ 1.  2.  3.  4.  6.  9.]
 [ 1.  4.  5. 16. 20. 25.]]  << include_bias=True
[[ 0.  1.  0.  0.  1.]
 [ 2.  3.  4.  6.  9.]
 [ 4.  5. 16. 20. 25.]]  << include_bias=False
'''

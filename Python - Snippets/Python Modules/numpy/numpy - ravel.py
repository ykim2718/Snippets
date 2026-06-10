"""
y, numpy - ravel.py, 2018.12.31
https://docs.scipy.org/doc/numpy-1.15.0/reference/generated/numpy.ravel.html
"""

print(__doc__)

import numpy as np
x = np.array([[1, 2, 3], [4, 5, 6]])
print(x)
print(x.reshape(-1))
print(np.ravel(x))

x = np.arange(12).reshape(2, 3, 2).swapaxes(1, 2)
print(x)
print(x.reshape(-1))
print('order=C', np.ravel(x, order='C'))
print('order=F', np.ravel(x, order='F'))
print('order=A', np.ravel(x, order='A'))
print('order=K', np.ravel(x, order='K'))


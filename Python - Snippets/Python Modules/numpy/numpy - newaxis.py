"""
y, numpy - newaxis.py, 2019.3.3
https://docs.scipy.org/doc/numpy/user/basics.indexing.html
"""

import numpy as np

x = np.arange(5)
print('-' * 22, '\n', x)
print('-' * 22, '\n', x[:, np.newaxis])
print('-' * 22, '\n', x[np.newaxis, :])
x = x[:, np.newaxis] + x[np.newaxis, :]
print('-' * 22, '\n', x)

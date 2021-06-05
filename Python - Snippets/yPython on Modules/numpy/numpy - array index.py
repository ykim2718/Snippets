"""
y, numpy - array index.py, 2019.3.3
"""

import numpy as np

x = np.arange(12).reshape(3, 4)
print('-' * 22, '\n', x)

indices = [1, 2]
print('-' * 22, '\n', x[indices])

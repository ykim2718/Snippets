"""
y, 2020.3.26
y, numpy - squeeze.py
"""

import numpy as np

print('-' * 32)
a = np.array([1, 2, 3])[:, np.newaxis]
print(a, a.shape)
# b = np.squeeze(a, axis=0)  # ValueError: cannot select an axis to squeeze out which has size not equal to one
b = np.squeeze(a, axis=1)
print(b, b.shape)
b = np.squeeze(a, axis=-1)
print(b, b.shape)


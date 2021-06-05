"""
y, 2020.3.26
y, numpy - expand_dims.py
"""

import numpy as np

print('-' * 32)
a = np.array([1, 2, 3])
print(a, a.shape)
b = np.expand_dims(a, axis=0)
print(b, b.shape)
b = np.expand_dims(a, axis=1)
print(b, b.shape)
b = np.expand_dims(a, axis=-1)
print(b, b.shape)

print('-' * 32)
a = np.arange(12).reshape(2, 3, 2)
print(a, a.shape)
b = np.expand_dims(a, axis=0)
print(b, b.shape)
b = np.expand_dims(a, axis=1)
print(b, b.shape)
b = np.expand_dims(a, axis=2)
print(b, b.shape)
b = np.expand_dims(a, axis=3)
print(b, b.shape)

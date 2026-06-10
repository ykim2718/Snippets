"""
y, 2020.6.29
numpy - vstack.py
"""

import numpy as np

print('1d'.ljust(32, '-'))
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
c = np.array([7, 8])
print(f"a.shape={a.shape}")
print(f"b.shape={b.shape}")
print(f"c.shape={c.shape}")
v = np.vstack([a, b])
print(f"v.shape={v.shape}")
try:
    v = np.vstack([a, b, c])
    print(f"v.shape={v.shape}")
except ValueError as ex:
    print(f"ValueError: {ex}")

print('2d'.ljust(32, '-'))
a = np.arange(6).reshape(2, 3)
b = np.arange(6).reshape(2, 3)
c = np.arange(3).reshape(3, 1)
print(f"a.shape={a.shape}")
print(f"b.shape={b.shape}")
print(f"c.shape={c.shape}")
try:
    v = np.vstack([a, b, c])
    print(f"v.shape={v.shape}")
except ValueError as ex:
    print(f"ValueError: {ex}")


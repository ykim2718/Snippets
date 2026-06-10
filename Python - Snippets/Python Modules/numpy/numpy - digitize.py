"""
y, 2022.8.10
numpy - digitize.py
https://numpy.org/doc/stable/reference/generated/numpy.digitize.html
"""

import numpy as np

x = np.array([-30, -10, -5, 0, 5, 10, 30])
print(f"{x=}")
bins = np.array([-10, -5, 5, 10])
right = np.digitize(x, bins, right=True)
print(f"{right=}")  # [0, 0, 1, 2, 2, 3, 4]
left = np.digitize(x, bins, right=False)
print(f"{left=}")  # [0, 1, 2, 2, 3, 4, 4]

inds = np.where(0 <= x, right, left)
print(inds)  # [0 1 2 2 2 3 4]

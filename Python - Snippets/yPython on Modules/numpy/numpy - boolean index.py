"""
y, numpy - boolean index.py, 2019.11.4
"""

import numpy as np
import pandas as pd


a = np.array([[10, 20, 30], [40, 50, 60]])
print(a, a.shape)  # (2, 3)
print(pd.DataFrame(a))
min_axis_0 = a.min(axis=0)  # [10 20 30], (3,)
min_axis_1 = a.min(axis=1)  # [10 40], (2,)
print((a > min_axis_0))  # [[False False False] [True True True]], (2, 3)
# print(a > min_axis_1)  # ValueError: operands could not be broadcast together with shapes (2,3) (2,)
print(a[a > min_axis_0])  # [40 50 60]



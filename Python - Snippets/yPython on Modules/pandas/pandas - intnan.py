"""
y, 2020.10.24
pandas - intnan.py
https://pandas.pydata.org/docs/reference/api/pandas.Int64Dtype.html#pandas.Int64Dtype
"""

import pandas as pd
import numpy as np


print(pd.__version__)
a = pd.Series([1, 2, pd.NA, None, np.nan])  # , dtype=pd.Int64Dtype)
print(a, a.dtype, type(a[0]), type(a[1]))

a = pd.Series([1.0, 2, pd.NA, None, np.nan])  # , dtype=pd.Int64Dtype)
print(a, a.dtype, type(a[0]), type(a[1]))

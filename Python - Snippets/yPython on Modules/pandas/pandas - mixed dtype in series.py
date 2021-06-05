"""
y, pandas - mixed dtype in series.py, 2018.9.30
"""

import pandas as pd
import numpy as np

if False:
    a = pd.Series(['a', None, np.nan, 1, 2.0])
else:
    a = pd.Series([], dtype=int)
    a[0] = 'a'  # trick to keep int type with float type numbers
    a[0] = 1.0
    a[1] = int(2)
for j in range(len(a)):
    print(j, a[j], type(a[j]))
print(a.dtype)


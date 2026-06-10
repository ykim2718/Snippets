"""
y, Pandas - series calc with shift.py 2017.9.18
"""

import pandas as pd
import numpy as np

ds = pd.Series(list(range(0, 4)), index=list('abcd'))

print(ds)
print(ds.shift(1))

ds = ds / ds.shift(1)
ds = ds.replace([np.inf, -np.inf], np.nan).dropna()

print(ds, ds.sum(), ds.prod(skipna=True))

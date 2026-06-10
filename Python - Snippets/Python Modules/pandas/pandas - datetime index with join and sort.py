"""
y, pandas - datetime index with join and sort.py, 2017.11.2
"""

import pandas as pd

di1 = pd.date_range('2017-11-1', '2017-11-5', freq='2d')
di2 = pd.date_range('2017-12-1', '2017-12-5', freq='2d')
di = di2.append(di1)
print(di1)
print(di2)
print(di)

ds = di.sort_value()
print(ds, type(ds))

"""
y, pandas - slice index.py, 2019.2.27
"""

import pandas as pd

a = pd.Series(list('abcdefghijklmnopqrstuvwxyz'))
index = slice(0, 9, 2)
print(a[slice(0, 9, 2)])
print(a[slice(-25)])
print(a[slice(5)])
print(a[[3, 4, 5]])

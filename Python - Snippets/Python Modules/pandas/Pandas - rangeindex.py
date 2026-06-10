"""
y, Pandas - rangeindex.py, 2017.9.2
"""

import pandas as pd
df = pd.DataFrame({1: [2, 3, 4]}, index=pd.RangeIndex(0, 3, 1))
df['add1'] = pd.RangeIndex(0, 30, 10)
df['add2'] = pd.RangeIndex(0, len(df), 1)
print(df)

"""
y, pandas - dataframe min max.py, 2018.10.14
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.max.html
"""

import pandas as pd

df = pd.DataFrame({'a': [1, 2], 'b': [3, 4]})
print(df)
print(df.min())  # axis='index'
print(df.max())  # axis='index'
print(pd.DataFrame(data=dict(min=df.min(), max=df.max())).T)
print('-'*8)
print(df.min(axis='columns'))
print(df.max(axis='columns'))

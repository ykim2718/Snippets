"""
y, pandas - flatten dataframe.py, 2019.1.21
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.stack.html
"""

import pandas as pd

s1 = pd.Series([1, 2], index=['code1', 'code2'], name='train')
s2 = pd.Series([3, 4], index=s1.index, name='test')
df = pd.concat([s1, s2], axis='columns')
print(df, type(df))
df = df.stack().to_frame().T
print(df)

"""
y, pandas - pivot table.py, 2018.9.10
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.pivot_table.html
"""

import pandas as pd
import numpy as np

df = pd.DataFrame({"A": ["foo", "foo", "foo", "foo", "foo",
                         "bar", "bar", "bar", "bar"],
                   "B": ["one", "one", "one", "two", "two",
                         "one", "one", "two", "two"],
                   "C": ["small", "large", "large", "small",
                         "small", "large", "small", "small",
                         "large"],
                   "D": [1, 2, 2, 3, 3, 4, 5, 6, 7]})
print(df)
table = pd.pivot_table(df, index=['A', 'B'], columns=['C'], values='D', aggfunc=np.sum)
print('\n', table)
table = pd.pivot_table(df, index=['A', 'C'], columns=None, values=['B', 'D'], aggfunc={'B': set, 'D': np.mean})
print('\n', table)

print('\n', '-'*32)
df = pd.DataFrame({'A': [1, 2, 3], 'B': [None]*3, 'C': [4, 5, 6]})
print(df)
table = pd.pivot_table(df, index=['A'], columns=None, values=['B', 'C'], aggfunc='last', dropna=False)
print('\n', table)



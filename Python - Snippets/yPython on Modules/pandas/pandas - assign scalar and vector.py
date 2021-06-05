"""
y, pandas - assign scalar and vector.py, 2019.4.3
"""

import pandas as pd

a = pd.DataFrame()
a.loc['A', 1] = 1
a.loc['B', 1] = 2
a.loc['B', 2] = 3
a.loc['B', 3] = 4
a.loc['C', 1] = 5
print('-' * 16 + '\n', a)
print('-' * 16 + 'sum of each column\n', a.sum(axis=0))  # sum of each column
print('-' * 16 + 'mean of each column\n', a.mean(axis=0))  # mean of each column
print('-' * 16 + 'mean of each column: fillna(0)\n', a.fillna(0).mean(axis=0))  # mean of each column
print('-' * 16 + 'sum of each row\n', a.sum(axis=1))  # sum of each row

a.loc['D'] = pd.Series([1, 2, 3], index=[3, 2, 1])
print('-' * 16 + '\n', a)

a.loc[:, 4] = pd.Series([10, 20, 30], index=list('BCD'))
print('-' * 16 + '\n', a)

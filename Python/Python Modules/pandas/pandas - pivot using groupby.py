"""
y, pandas - pivot using groupby.py, 2018.9.10
https://stackoverflow.com/questions/39648991/pandas-dataframe-pivot-memory-error
"""

import pandas as pd

df = pd.DataFrame({'A': [1, 2, 3], 'B': [None]*3, 'C': [4, 5, 6], 'D': list('abb')})
print('\n', df)
table = pd.pivot_table(df, index=['A', 'D'], columns=None, values=['B', 'C'], aggfunc='last', dropna=False)
print('\n', table)

index_columns = ['A', 'D']
value_columns = ['B', 'C']
# table = df.groupby(['A'])['B', 'C'].last()  # ok
table = df.groupby(index_columns)[value_columns].last()
print('\n', table)
table = df.groupby(index_columns).agg({k: 'last' for k in value_columns})
print('\n', table)



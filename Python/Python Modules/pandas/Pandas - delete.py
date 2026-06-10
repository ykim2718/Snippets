"""
y , 2016.4.25 - 7.20, Pandas - delete.py
"""
import pandas as pd
import numpy as np

df = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [4, None, float('nan')],
    'c': [7, 8, 9],
    'd': ['1', '2', '3'],
}, index=['r1', 'r2', 'r3'])
print(df)

print('y, 2016.5.2 Drop row or column')
print("df.drop['r1'], axis=0\n", df.drop(['r1'], axis=0))  # drop a row
print("df.drop('r1', axis=0)\n", df.drop('r1', axis=0))  # drop a row
print("df.drop('a', axis=1)\n", df.drop('a', axis=1))  # drop a column

print('y, 2016.7.20, Drop row or column conditionally')
print("df[~(df['a']==2)]\n", df[~(df['a'] == 2)])  # drop rows with condition
print("df[df.a!=2]\n", df[df.a != 2])  # drop rows with condition
print("df.dropna(subset=['b'])\n", df.dropna(subset=['b']))
print("df.dropna(subset=['a', 'b'], how='any')\n",
      df.dropna(subset=['a', 'b'], how='any'))  # all, any
print("df.dropna(subset=[df.columns], how='any')\n",
      df.dropna(subset=[df.columns], how='any'))  # all, any
print("df[np.isfinite(df['b'])]\n", df[np.isfinite(df['b'])])
print("df[pd.notnull(df['b'])]\n", df[pd.notnull(df['b'])])
print("df[~df['b'].isnull()]\n", df[~df['b'].isnull()])

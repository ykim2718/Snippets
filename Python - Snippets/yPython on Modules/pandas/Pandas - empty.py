"""
y (copyRight) Pandas - empty.py, 2016.7.28
"""
import pandas as pd
import numpy as np

df = pd.DataFrame(index=range(2))
print(df.empty)
df['a'] = ''
df['b'] = None
df['c'] = float('nan')
df['d'] = np.nan
df['e'] = pd.Series([])
print(df)
print(df.empty)
print(df['a'].empty, df['b'].empty, df['c'].empty, df['d'].empty, df['e'].empty)
print(len(df['a']), len(df['b']), len(df['c']), len(df['d']), len(df['e']))

df.ix[0, 'a'] = 1
print(type(df['a'][0]))

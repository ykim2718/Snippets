"""
y, pandas - reduce memory by category dtype.py, 2018.9.11
https://stackoverflow.com/questions/43711843/reduce-memory-dedicated-to-pandas-dtype-object
"""

import pandas as pd
import numpy as np

size = 10**6
df = pd.DataFrame({'A': np.random.choice(['Y', 'N'], size=size), 'B': np.random.randint(0, 9, size=size)})
print(df.head(2))
print(df.info(memory_usage='deep'))

print('-'*32)

df['A'] = df['A'].astype('category')
print(df.head(2))
print(df.info(memory_usage='deep'))

print('-'*32)

df['B'] = df['B'].astype('category')
print(df.head(2))
print(df.info(memory_usage='deep'))

print('-'*32)

# check original data type
cell = df.loc[0, 'B']
print(cell, type(cell))
series = df.loc[0:10, 'B']
print(series.dtype, type(series))
row_dict = df.loc[0, df.columns].to_dict()
print(row_dict, type(row_dict))



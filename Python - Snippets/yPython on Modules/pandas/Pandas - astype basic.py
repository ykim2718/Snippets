"""
y, Pandas - astype basic.py, 2017.9.27; 2019.5.16
"""

import pandas as pd
import numpy as np

print('--- 20170917 --- ' * 4)

df = pd.DataFrame([[0, 1, 2, 3], [4, 5, 6, 7]], columns=list('abcd'))
df = pd.DataFrame(0, index=[0, 1], columns=list('abcd'))
print(df)
print(df.dtypes)
df['a'] = df['a'].astype(float)
df = df.astype(dtype={'b': float, 'c': np.int32})
print(df)
print(df.dtypes)

print('--- 20190516 --- ' * 4)

try:
    df = pd.DataFrame([None, 1, 2.3, ''])
    print(df.astype(float))
except ValueError as ex:
    print(ex.__class__.__name__, ex)

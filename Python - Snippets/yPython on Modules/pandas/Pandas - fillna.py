"""
y, Pandas - fillna.py, 2017.6.7
"""

import pandas as pd
import numpy as np

df = pd.DataFrame([[1, 2, 3],
                   [4, np.nan, 6],
                   [7, np.nan, 9],
                   [10, 11, 12],
                   [np.nan, np.nan, 15]],
                   columns=list('abc'))

print(df)
_ffill, _bfill, _pad = 'ffill', 'bfill', 'pad'
a = 'df.fillna(method=_ffill, axis=0)'  # same as 'pad'
print('>> %s \n' % a, eval(a))
a = 'df.fillna(method=_ffill, axis=1)'
print('>> %s \n' % a, eval(a))
a = 'df.fillna(method=_bfill, axis=0)'  # same as 'backfill'
print('>> %s \n' % a, eval(a))
a = 'df.fillna(method=_bfill, axis=1)'
print('>> %s \n' % a, eval(a))

print('-' * 16)
df[['b']] = df[['b']].fillna(method=_ffill, axis=0)
print(df)

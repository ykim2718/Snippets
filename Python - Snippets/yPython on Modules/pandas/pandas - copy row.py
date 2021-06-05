"""
y, pandas - copy row.py, 2017.9.6
"""

import pandas as pd
df = pd.DataFrame({'a': [3, 4, 5],
                   'b': [6, 7, 8],
                   'c': [9, 10, 11]},
                  index=list('xyz'))
df.loc['x', ['a', 'b']] = 100, 200
df.loc['y', ['b', 'c']] = df.loc['x', 'a'], df.loc['x', 'b']
df.loc['z', ['a', 'c']] = tuple(df.loc['x', ['a', 'b']].tolist())
print(df)
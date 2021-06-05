"""
y, pandas - multiindex.py, 2019.7.5, 7.11, 7.13
https://pandas.pydata.org/pandas-docs/stable/user_guide/advanced.html
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.MultiIndex.html
"""

import pandas as pd

iterables = [['bar', 'baz', 'foo', 'qux'], ['one', 'two']]
index = pd.MultiIndex.from_product(iterables, names=['first', 'second'])

print(index)
print(index.levels[-1])

index = pd.Index([('bar', 1), ('baz', 2), ('foo', 3), ('qux', 4)])
print(index.levels[-1])

print('-'*32)
df = pd.DataFrame(columns=['a', 'b', 'c'], index=['r1'])
print(df)
# df.index.name = 'index1'
df = df.set_index([df.index, 'a'])
print(df)
print(df.index)

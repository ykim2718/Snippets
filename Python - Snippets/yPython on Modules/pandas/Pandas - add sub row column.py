"""
y, 2016.5.2, Pandas - add sub row column
"""

import pandas as pd

print('y, 2016.4.25')
df = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [4, 5, 6],
    'c': [7, 8, 9],
    'd': [10, 11, 12]},
    index=[0, 1, 2])

print('y, 2016.5.2 Subtract row or column')
col = ['a', 'b', 'c']
df['new_col'] = col  # add one column
row = ['a', 'b', 'c', 'd', 'e']
df.loc['new_row'] = row  # add one row, in-place editing
# Be sure that 'new_row' index should be new to df.
# Otherwise new will overwrite old.
row = ['a', 'b', 'c', 'D', 'F']  # 2016.5.19
df.iloc[-1] = row  # Note that last row is replaced instead of adding row
# df.iloc[len(df)] = row  # IndexError: single positional indexer is out-of-bounds
print(df)

print('y, 2016.5.2 Drop row or column')
print('df.drop([0], axis=0)\n', df.drop([0], axis=0))  # drop a row
print('df.drop(1, axis=0)\n', df.drop(1, axis=0))  # drop a row
print('df.drop("a", axis=1)\n', df.drop('a', axis=1, inplace=True))  # drop a column

print(df[0:1])  # Be careful about indexing like a label, not positional indexing, use df.iloc[0:1]

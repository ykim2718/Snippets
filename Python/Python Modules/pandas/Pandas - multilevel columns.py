"""
y, Pandas - multilevel columns, 2016.5.27; 2019.7.13
Pandas Multilevel column names
http://stackoverflow.com/questions/21443963/pandas-multilevel-column-names
"""

import pandas as pd


print('-'*32)
df = pd.DataFrame({'a': [1, 2, 3], 'b': [4, 5, 6]})
columns = [('c', 'a'), ('c', 'b')]
df.columns = pd.MultiIndex.from_tuples(columns, names=('first', 'second'))
print(df)
print(df.columns.levels[df.columns.names.index('first')])

print('-'*32)
df = pd.DataFrame(columns=['a', 'b', 'c'], index=['r1'])
print(df)
# df.index.name = 'index1'
print("df.set_index([df.index, 'a'])=\n", df.set_index([df.index, 'a']))

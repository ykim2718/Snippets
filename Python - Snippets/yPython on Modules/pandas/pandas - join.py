"""
y, 2016.7.16 - 7.25, pandas - join.py
"""
import pandas as pd

df = pd.DataFrame({'c1': [1, 2, 3]}, index=['r1', 'r2', 'r3'])
dg = pd.DataFrame({'c2': [4, 5, 6]}, index=['r1', 'r2', 'r3'])
dh = pd.DataFrame({'c3': [7, 8, 9]}, index=['r1', 'r2', 'r3'])
di = pd.DataFrame({'c4': ['a', 'b', 'c']}, index=df.index)
dj = pd.DataFrame(dict(c5=['d', 'e']))
dk = pd.DataFrame(dict(c4=['f']), index=['r1'])

dx = pd.concat([df, dg, dh, di, dj, dk], axis=1)
print(dx)

dy = pd.concat([df, dg, dh, di, dj, dk], axis=0)
print(dy)

print('y, 2016.7.20, Combine tow columns of text in dataframe in pandas/python')
df = pd.concat([df, dg, dh, di], axis=1)
df['c1+c2'] = df[['c1', 'c2']].apply(lambda x: '{},{}'.format(x[0], x[1]), axis=1)
df['c1+c3'] = df['c1'].map(str) + ',' + df['c3'].map(str)
print(df)

print('y, 2016.7.25, Add a column from a list')
df['series'] = dj['c5'].values.tolist() + [None] * (df.shape[0] - len(dj['c5']))
print(df)

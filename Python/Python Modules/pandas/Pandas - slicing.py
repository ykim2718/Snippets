"""
y, 2016.4.25
"""

import pandas as pd

print('y, 2016.4.25')
df = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [4, 5, 6],
    'c': [7, 8, 9],
    'd': [10, 11, 12]},
    index=[0, 1, 2])

print("\ny, 2016.4.12 - 25, df query with keys")
keys = [3, 4]
print("df[df.a.isin(keys)]=\n", df[df.a.isin(keys)])
print("df[df['a'].isin(keys)]=\n", df[df['a'].isin(keys)], type(df[df['a'].isin(keys)]))
print("df.query('a in @keys')=\n", df.query('a in @keys'))

print('\ny, 2016.4.25 - 26, conditional row slicing')
print("df.ix[df.index > 1 ]=\n", df.ix[df.index > 1])
print("df.ix[:,'c':]=\n", df.ix[:, 'c':])
print("df[df.a == 2]=\n", df[df.a == 2])
print("df[df['a'] == 2]=\n", df[df['a'] == 2])
print("df[~(df['a'] == 2)]=\n", df[~(df['a'] == 2)])
print("df.loc[[0,2]]=\n", df.loc[[0, 2]])
print("df.loc[df.index[[0,2]],:]=\n", df.loc[df.index[[0, 2]], :])
print("df.ix[df.index[[0,2]],:])=\n", df.ix[df.index[[0, 2]], :])  # different from the above line
print("df.ix[df['d']<11,'a']=\n", df.ix[df['d'] < 11, 'a'])
print("df.ix[df.index<3,'d']=\n", df.ix[df.index < 3, 'd'])
print("df.ix[df.index[[0,2]],'d']=\n", df.ix[df.index[[0, 2]], 'd'])
print("df.ix[:,[0,3]]=\n", df.ix[:, [0, 3]])
print("df[-2:]=\n", df[-2:])

print("y, 2016.5.1 Row selection by boolean list with size of len(index)")
print(df.ix[[False, True, True]])

print("y, 2016.5.6 Create dummy DataFrame copying index")
df = pd.DataFrame({}, index=df.index, columns=['entry'])
print(df)

print("y, 2016.5.11 Select rows with null or notnull")
df = pd.DataFrame({'a': [1, float('nan'), 3], 'b': [float('nan'), 22, 33]})
print(df[pd.isnull(df['a'])])
print(df[pd.notnull(df['b'])])
print(df[pd.isnull(df).any(axis=1)])

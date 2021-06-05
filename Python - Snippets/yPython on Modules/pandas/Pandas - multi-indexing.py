"""
y, Pandas - multi-indexing.py, 2016.6.15 - 10.24
"""
import pandas as pd

df = pd.DataFrame(columns=['a', 'b', 'FIRST', 'SECOND'])
print(df)

df.set_index(['FIRST', 'SECOND'], inplace=True)
df.index.names = ('1st', '2nd')  # 2016.7.31
print(df)

if isinstance(df.index, pd.MultiIndex):
    indices = df.index.names
    print(indices)
    df.reset_index(level=indices, inplace=True)
    df.to_excel('test.xlsx', index=True)
    print(df.columns)
    df.set_index(indices, inplace=True)

index = ('A', 1)
df.ix[index, 'a'] = 2
index = ('B', 1)
df.ix[index, 'a'] = 3
df.ix[index, 'b'] = 4
print(df)

dg = df.loc[df.index.get_level_values('1st') == 'A']
print(dg)

"""
try:
    dh = df.ix[df.index.get_level_values('2nd') == '1']
except KeyError as ex:  # very strange behavior happening only to the 2nd index
    dh = pd.DataFrame()
print(dh)

print('y, 2016.7.31, Reset index and set index')
df.reset_index(inplace=True)
df.set_index('1st', inplace=True)
print(df)
"""

print("y, 2016.10.24, Double index swapped each other")
df.index = df.index.swaplevel(0, 1)
print(df)


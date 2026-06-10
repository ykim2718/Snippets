import pandas as pd

print('y, 2016.4.29 ' + '-' * 32)
df = pd.DataFrame({
    'a': [1, float('nan'), float('nan')],
    'b': [4, 5, float('nan')],
    'c': [7, 8, 9],
    'd': [10, 11, 12]},
    index=[0, 1, 2])
print(df, "\n--------------")
print(df.dropna(thresh=2), "\n" + '-' * 8)  # not working
print(df[pd.notnull(df['b'])], "\n" + '-' * 8)
print(df[[True, False, True]], "\n" + '-' * 8)
"""
a=pd.notnull(df['a'])
b=pd.notnull(df['b'])
print(a | b)
"""
print(df[pd.notnull(df['a']) | pd.notnull(df['b'])], '\n' + '-' * 8)  # 2016.4.29

print('y, 2016.10.30 ', '-' * 32)
df = pd.DataFrame({
    'a': [1, float('nan'), float('nan')],
    'b': [4, 0, float('nan')]})
df = df.loc[~(df == 0).any(axis=1)]
print(df, '\n' + '-' * 8)
df = df[~(df['a'] == 1)]
print(df, '\n' + '-' * 8)

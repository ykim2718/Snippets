"""
y, 2016.4.25 - 5.1
"""

import pandas as pd

print('y,2016.4.25, each row max')
data = {'name': ['kim', 'lee', 'park'],
        'test1': [92, 96, 88],
        'test2': [88, 92, 60],
        'test3': [84, 88, 95]}

df = pd.DataFrame(data)

df['max'] = df[['test1', 'test2', 'test3']].max(axis=1)
print(df)

print('\ny, 2016.4.25, each col max')
r = df.max()
print(r)
print("r['test1'], r['test2'], r['test3']=", r['test1'], r['test2'], r['test3'])
print("df.max()['test1']=", df.max()['test1'])
print("df['test1'].max()=", df['test1'].max())
print("max(df['test1'].max(), df['test2'].max())=", max(df['test1'].max(), df['test2'].max()))

print('y, 2016.4.30, Rolling mean with customized window with Pandas')
date1 = '2016-04-25'
date2 = '2016-04-30'
dates = pd.date_range(date1, date2, freq='2d').tolist()
data = range(len(dates))
df = pd.DataFrame({'data': data}, index=dates)
rmean = pd.rolling_mean(df['data'], window=2)
df = pd.concat([df, rmean], axis=1)
print(df)

print("y, 2016.5.1 Column to column comparison")
df = pd.DataFrame({'a': range(5), 'b': list(reversed(range(5))), 'c': range(5, 10)})
df.ix[df.index[-1], 'b'] = float('nan')
print(df)
print(df[df['a'] > 3])
print(df[df['a'] > df['b']])

print("y, 2016.5.1 Row to row comparison")
df = pd.DataFrame({'a': range(5), 'b': list(reversed(range(5))), 'c': range(5, 10)})
r = df.diff(periods=2, axis=0)  # {0 or ‘index’, 1 or ‘columns’}, default 0
print(df, "\n", r)

print("y, 2016.5.3 - 5.5 Row to row calculation")
df = pd.DataFrame({'a': range(5), 'b': list(reversed(range(5))), 'c': range(5, 10)})
df['diff'] = df['a'].diff(2)
df['sum'] = df.sum(axis=1)
df['sum'] = df[['a', 'b']].sum(axis=1)
df['a-b'] = df['a'] - df['b']  # 2016.5.5
df['a/b'] = df['a'] / df['b']  # 2016.5.5
df['a>b'] = df['a'] > df['b']  # 2016.5.5
print(df)

print("y, 2016.5.3 - 5.5 Row to row calculation")
df = pd.DataFrame(data={'a': [1, -1, 2, -2], 'b': [3, -3, -2.3, 0.7]})
df['abs'] = df['b'].abs()
print(df, df['abs'].sum(), df['b'].abs().sum())

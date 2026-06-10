"""
Y. Kim, 2016.4.12 - 17
http://pandas.pydata.org/pandas-docs/stable/dsintro.html
"""

import pandas as pd

# Y, 2016.4.12
d = {'one': [1, 3, 2, 4],
     'two': [44, 22, 22, 11]}
df = pd.DataFrame(d, index=['a', 'b', 'c', 'd'])
print(df)
print('df.index=', df.index)
print('len(df.index)=', len(df.index))
print('df.columns=', df.columns)
print("df.shape=", df.shape)
print("pd.DataFrame().shape=", pd.DataFrame().shape)
print("type(df)=", type(df))
print("isinstance(df,pd.DataFrame)=", isinstance(df, pd.DataFrame))
print(df.head(2))
print(df.tail(1))

# Y, 2016.4.12
for index, row in df.iterrows():
    print("index=", index, end="")
    for col in row:
        print(" val=%s" % col, end="")
    print("")

# Y, 2016.4.16
print("\ny, 2016.4.16")
df.rename(columns={'one': 'ONE', 'two': 'TWO'}, inplace=True)
df['Append-1'] = 1
df['Append-2'] = 2
print(df)

# Y, 2016.4.17
print(list(df.columns.values))
print(df.columns.values.tolist())
print(list(df))

# Y, 2016.4.17
df.rename(columns={'Append-1': 'THREE'}, inplace=True)
df.columns = df.columns.str.replace("Append-2", "FOUR")
print(df.columns)

# Y, 2016.4.17
for i in [1, 2, 3]: df.ix[i, 'FOUR'] = i
print(df)
unique = df['FOUR'].unique()
print(unique)

df_add = pd.DataFrame({
    'ONE': ['A8', 'A9', 'A10', 'A11'],
    'B': ['B8', 'B9', 'B10', 'B11'],
    'C': ['C8', 'C9', 'C10', 'C11'],
    'D': ['D8', 'D9', 'D10', 'D11']},
    index=[8, 9, 10, 11])
# df = pd.concat([df, df_add], axis=0, join='outer')
df = df.append(df_add)
print(df)

# y, 2016.4.22
print('\ny, 2016.4.22')
date_list = pd.date_range(pd.datetime.today(), periods=4).tolist()
print("\ny, 2016.4.22")
d = {'date': date_list, 'one': range(0, 4), 'two': range(4, 8)}
df = pd.DataFrame(d)
print(df)
df['date'] = df['date'].apply(lambda x: x.date())
df.set_index('date', drop=True, inplace=True)
print(df)

# y, 2016.4.23
print('\ny, 2016.4.23')
df = pd.DataFrame({'out': [1]})


def pd_in_func(df): df = pd.DataFrame({'in': [1, 2]})


pd_in_func(df)
print(df)
print(df.info())

# y, 2016.4.23
print('\ny, 2016.4.23, check whether list value is changed')
a = [1, 2]
b = [3, 4]
df = pd.DataFrame({'a': a, 'b': b})
df.iloc[0][1] = 22
b[0] = 33
print(df, a, b)

print('\ny, 2016.4.24, append row list')
df = pd.DataFrame(columns=['col 1', 'col 2'])
df = df.append(pd.Series(['a', 'b'], index=['col 1', 'col 2']), ignore_index=True)
df = df.append(pd.Series(['d', 'e'], index=['col 1', 'col 2']), ignore_index=True)
print(df)

print('\ny, 2016.4.24, merge columns')
df = pd.DataFrame({'col#1': ['a', 'b'], 'col#2': ['c', 'd']})
df2 = pd.DataFrame({'col#1': [1, 2], 'col#4': [3, 4]})
df = pd.merge(df, df2, how='outer', on=['col#1'], )
print(df)

print('\ny, 2016.4.24, append column list')
df = pd.DataFrame({'col#1': ['a', 'b'], 'col#2': ['c', 'd']}, index=['1st', '2nd'])
df['new1'] = ['o', 'p']
df = df.append([1, 2])
df = df.append(pd.DataFrame({'new2': [3]}), ignore_index=True)
df = pd.concat([df, pd.DataFrame({'new3': [4, 5]})], axis=0, join='outer')
print(df)

""" pending
print('\ny, 2016.4.24, append column list')
df1 = pd.DataFrame({'#1':['a', 'b']},index=['1st','2nd'])
df2 = pd.DataFrame({'#2':['a', 'b', 'c']})
index_new = df1.index
df2.set_index(index_new)
df = df1.append(df2)
print(df)
"""

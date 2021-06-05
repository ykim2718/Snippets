"""
Y. Kim, 2016.4.12 - 10.23
http://pandas.pydata.org/pandas-docs/stable/dsintro.html
"""

import pandas as pd

print("\ny, 2016.4.12 - 25")
df = pd.DataFrame(
    {'A': ['a', 'b', 'c'], 'B': ['d', 'e', 'f'], 'C': ['g', 'h', 'i'], 'D': ['o', 'p', 'q']},
    index=[10, '2ab', 30]
)
print(df)
for c, col in enumerate(df.columns):  # c for integer indexing, col for label indexing
    # df[col] = df[col].astype(float) # don't know exactly
    for r, row in enumerate(df.index):  # r for integer indexing, row for label indexing
        value = df[col][row]
        if value == 'a': df.iloc[r, c] = 1.1  # integer (positional) indexing
        if value == 'b': df.iloc[r][c] = 2.2  # integer (positional) indexing
        if value == 'c': df.ix[row, col] = "3.xx"  # label indexing
        if value == 'd': df[col].ix[row] = 4.2  # label indexing
        if value == 'e': df[col].iloc[r] = 5.2  # label and integer indexing
        if value == 'f': df.set_value(row, col, 6)  # label indexing
        if value == 'g': df[col][row] = 7.4  # label indexing
        if value == 'h': df[df == value] = 8.8  # boolean indexing
        if value == 'i': df.values[r, c] = 9.1  # integer indexing
        if value == 'o': df.loc[row, col] = 10.11  # label indexing
        # if value == 2.0: df.iloc[row]=dict(one='2.34',two='5.67') ?????
print(df)

print("y, 2016.4.30, Retrieving column index from column name in python pandas")
print('df.columns.get_loc("B")=', df.columns.get_loc("B"))
i = df.columns.get_loc("B")
print("df.columns[i]=", df.columns[i])

print("y, 2016.4.12, 10.16, Reset DataFrame index, keeping or removing index")
case = 2
if case == 0:  # removing
    df.reset_index(drop=True, inplace=True),
elif case == 1:  # keeping
    df.reset_index(drop=False, inplace=True),
elif case == 2:  # keeping
    df['keep_index'] = df.index
    df.reset_index(drop=True, inplace=True)
print(df)


print("y, 2016.4.21, Set a column to index")
print(df.index.name)
df.set_index('A', inplace=True)
df.index.name = 'AAA'
print(df)

print("y, 2016.4.21, Set indices")
df.index = ['aaa', 'bbb', 'ccc']
print(df)

print("y, 2016.4.17, Set column names")
df.columns = ['1st', '2nd', '3RD', '4th']
df.columns.values[2] = '3rd'  # 2016.5.29
print(df)

print("y, 2016.4.17, Replace column names")
df.rename(columns={'1st': 'First'}, inplace=True)
df.columns = df.columns.str.replace("2nd", "Second")
print(df)

print("y, 2016.4.12, Set index name")
df.index.name = "#"
print(df)

print("y, 2016.5.2, row - column indexing")
c_int = df.columns.get_loc('3rd')
r_start = df.index.get_loc('bbb')  # 2016.5.7
for r_int in range(r_start, len(df)):
    val = df.iloc[r_int, c_int]
    print("r %d, c %d =>" % (r_int, c_int), val)

print()
print("y, 2016.5.6, Add column at specified rows")
df.ix[[1, 2], '4th'] = [1, 2]
print(df)

print()
print("y, 2016.5.8, Get list of index satisfying column condition")
print(df[df['4th'] > 1].index.tolist())

print()
print("y, 2016.5.11, Start loop from the selected row")
r_start = df.index[df.index.get_loc('bbb') - 1]
for row in df[r_start:].index:
    print(row)

print()
print("y, 2016.6.1, Convert a row in pandas into list")
for row in df.iterrows():
    index, data = row
    print(index, data)
a_list = df.apply(lambda x: x.tolist(), axis=1)

print()
print("y, 2016.6.12, Convert a row in pandas into list")
df = df.loc[[df.index[0], df.index[-1]], :]
print(df)

print()
print("y, 2016.6.17, How to select all columns, except one column")
# df = df.loc[:, df.columns != '3rd']     # working
# df_dropped = df.pop('3rd')      # working
df.drop(['3rd'], axis=1, inplace=True)
print(df)

print()
print("y, 2016.10.23, Find date index nearest to a given date")
import numpy as np
import datetime as dt
df_index = pd.date_range(start=dt.date(2016, 4, 1), end='2016-10-23', freq='B')  # do not care string or datetime
print(type(df.index[0]))  # class str, but DateTimeIndex with dtype='datetime64[ns]'
df = pd.DataFrame(data=list(range(len(df_index))), index=df_index, columns=['count'], dtype=int)
print(df.tail(7))
x = '2016-12-25'  # IndexError: index 206 is out of bounds .....
x = '2016-10-25'  # Saturday, then nearest day will be 2016-10-17 for sorted array, while 14 for non-sorted array
x = dt.date(2016, 10, 15)
if True:
    idx = np.searchsorted(df.index, x)  # search in sorted array
else:
    if isinstance(x, (dt.datetime, dt.date, dt.time)):
        x = np.datetime64(x)
    idx = (np.abs(df.index - x)).argmin()  # search in non-sorted array
print('df.index[idx] =', df.index[idx], type(df.index[idx]))


# df.iloc[r, c] = df.iloc[r, c_price]  # working but irritating caveats
# df.iloc[r, c] = df.values[r, c_price]  # working bug aggravating caveats

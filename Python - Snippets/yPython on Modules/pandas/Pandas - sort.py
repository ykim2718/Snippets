"""
y, Pandas sort.py, 2016.4.12 - 10.24, 2017.6.20

"""
import pandas as pd

print_ = lambda x: print('-' * 32, '\n', x, sep='')  # 2017.6.20

print("2016.4.12")
df = pd.DataFrame(
    {'one': [1, 3, 2, 4],
     'two': [44, 22, 22, 11],
     'three': [7, 6, 5, 4]},
    index=['a', 'b', 'd', 'c'])
print(df)

print("2016.4.19, Sort columns by column name")
cols = df.columns.tolist()
cols.sort(reverse=True)
df = df[cols]
print(df)
df.sort_index(axis=1, ascending=True, inplace=True)  # 2016.7.18
print(df)

print('2016.7.18, Sort columns by an arbitrary sequence')
df = df[['two', 'one', 'three']]
print(df)
cols = ['three']
cols.extend([x for x in df.columns if x not in cols])
df = df[cols]
print(df)
df = df.reindex(columns=sorted(cols))
print(df)

print("2016.4.21, Sort all by sorting specific columns")
df.sort_values(by=['two', 'three'], inplace=True)
df.sort_values(by=['two', 'three'], ascending=[True, False], inplace=True)
print(df)

print("2016.4.26, Sort all by index")
df.sort_index(inplace=True)
print(df)

print_("2016.10.18, How to sort a pandas dataframe by columns and a part of multi index simultaneously")
# http://stackoverflow.com/questions/20613844/how-to-sort-a-pandas-dataframe-by-columns-and-a-part-of-multi-index-simultaneous
import numpy as np
mi1 = pd.MultiIndex.from_tuples([('bar', 'y'), ('bar', 'z'), ('baz', 'y'), ('baz', 'z'), ('foo', 'y'), ('foo', 'z')],names=['first','second'])
df = pd.DataFrame(np.random.randn(6), index=mi1)
print(df)
df = df.reset_index().sort_values(by=['second', 0]).set_index(df.index.names)
print(df)

print("2014.10.24, 2017.6.20, Sort by individual index in multi-index")
#df = df.reset_index().sort_values(by=['first'], ascending=False).groupby('first', sort=False).apply(
#    lambda s: s.sort_values(by=['second'], ascending=[True]).set_index(df.index.names))
df = df.reset_index().sort_values(by=['first', 'second'], ascending=[True, False]).set_index(df.index.names)
print(df)

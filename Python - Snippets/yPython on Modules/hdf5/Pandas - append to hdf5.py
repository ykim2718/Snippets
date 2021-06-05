"""
y, Pandas - append to hdf5.py, 2017.5.30

How does one append large amounts of data to a Pandas HDFStore and get a natural unique index?
    https://stackoverflow.com/questions/16997048/how-does-one-append-large-amounts-of-data-to-a-pandas-hdfstore-and-get-a-natural

"""

my_file = 'Pandas - append to hdf5.h5'

import pandas as pd
import numpy as np
import os

files = ['test1.csv','test2.csv']
for f in files:
    pd.DataFrame(np.random.randn(10, 2), columns=list('AB')).to_csv(f)

df1 = pd.DataFrame(['a', 'ab'], columns=list('A'))
df1.index.name = 'df1'
# df2 = pd.DataFrame(['1', '1234'], columns=list('A'))  # bigger item size causes error
df2 = pd.DataFrame([['1', '12'], [10, 20]], columns=list('AB'))  # new column causes error
df2.index.name = 'df2'
print(df1)
print(df2)

if os.path.exists(my_file):
    os.remove(my_file)

with pd.get_store(my_file) as store:
    """
    for f in files:
        df = pd.read_csv(f, index_col=0)
    """
    for df in [df1, df1]:
        try:
            nrows = store.get_storer('foo').nrows
        except:
            nrows = 0

        df.index = pd.Series(df.index) + nrows
        store.append('foo', df)

print(pd.read_hdf(my_file, 'foo'))

#----------------------------------------------------------------

import h5py

f = h5py.File(my_file, 'r', libver='latest')
f.visit(lambda name: print(name))
print("name: %s, keys: %s, values: %s" % (f.name, f.keys(), f.values()))
group_key = list(f.keys())[0]
print(group_key)
print(list(f[group_key+'/table']))
print(list(f[group_key+'/_i_table/index/indices']))
print(list(f[group_key+'/_i_table/index/sorted']))
print(f['foo']['table'])
print(f['foo']['table'][:])
print(dir(f['foo']['table'].attrs))
for key, value in f['foo']['table'].attrs.items():
    print(key, '=', value)
f.close()
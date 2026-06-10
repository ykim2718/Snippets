"""
y, h5py - read pandas in hdf.py, 2017.5.31

Save pandas DataFrame using h5py for interoperability with other hdf5 readers
    https://stackoverflow.com/questions/30773073/save-pandas-dataframe-using-h5py-for-interoperabilty-with-other-hdf5-readers

"""

my_file = 'h5py - read pandas in hdf.h5'

import pandas as pd
import h5py

NaN = float('nan')
ID = [1, 2, 3, 4, 5, 6, 7]
A = [NaN, NaN, NaN, 0.1, 0.1, 0.1, 0.1]
B = [0.2, NaN, 0.2, 0.2, 0.2, NaN, NaN]
C = [NaN, 0.5, 0.5, NaN, 0.5, 0.5, NaN]
columns = {'A':A, 'B':B, 'C':C}
df = pd.DataFrame(columns, index=ID)
df.index.name = 'ID'
print(df)

df.to_hdf(my_file, 'df', mode='w', format='table', data_columns=True)
print(my_file, '.. saved')

h = h5py.File(my_file)
print(h['df']['table'])
print(h['df']['table'][:])
for key in h['df']['table'].attrs.keys():  # causing error, don't know
    print(key)
    print('value = ', h['df']['table'].attrs.get(key, None))
h.close()

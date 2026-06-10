"""
y, pandas hdf5 - read write hdf5.py, 2018.9.5, 9.14
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.to_hdf.html
https://www.pythonforthelab.com/blog/how-to-use-hdf5-files-in-python/
"""

import pandas as pd
import os

_module_name = os.path.splitext(os.path.basename(__file__))[0]
hdf5_name = "%s.h5" % _module_name

df = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6]}, index=['a', 'b', 'c'])
df.to_hdf(hdf5_name, key='frame', mode='w')

s = pd.Series([1, 2, 3, 4])
s.to_hdf(hdf5_name, key='series')

print(pd.read_hdf(hdf5_name, 'frame'))
print(pd.read_hdf(hdf5_name, 'series'))

print('\n')

import h5py

with h5py.File(hdf5_name, 'r') as f:
    for k in f.keys():
        print(k)



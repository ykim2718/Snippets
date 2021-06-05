"""
y, pandas hdf5 - read hdf5 with chunksize.py, 2018.9.17
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.read_hdf.html
"""

import pandas as pd
import h5py

hdf5_name = 'test.h5'

with h5py.File(hdf5_name, 'r') as f:
    for k in f.keys():
        print(k)


frame_it = pd.read_hdf(hdf5_name, 'data', chunksize=1e5)  # chunksize = number of rows
for j, frame in enumerate(frame_it):
    print(j, len(frame))
print(frame.head())
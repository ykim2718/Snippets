"""
y, h5py - example 1st.py, 2017.5.30

h5py Quick Start Guide
----------------------
http://docs.h5py.org/en/latest/quick.html
An HDF5 file is a container for two kinds of objects: datasets, which are
array-like collections of data, and groups, which are folder-like containers
that hold datasets and other groups.

"""

import h5py
import numpy as np

f = h5py.File("mytestfile.hdf5", "w")
dset = f.create_dataset("mydataset", (100,), dtype='i')
print(f.name, dset.name, dset.shape, dset.dtype)

dset[...] = np.arange(100)
print(dset[0:100:10])

grp = f.create_group("subgroup")
dset2 = grp.create_dataset("another_dataset", (50,), dtype='f')
print(dset2.name)

dset3 = f.create_dataset('subgroup2/dataset_three', (10,), dtype='i')
print(dset3.name)

dataset_three = f['subgroup2/dataset_three']

for name in f:
    print(name)

f.close()


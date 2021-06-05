"""
y, h5py - basic.py, 2017.5.30
"""

import h5py

my_file = 'h5py - basic.hdf5'

f = h5py.File(my_file, 'w')

dt = h5py.special_dtype(vlen=str)
dset = f.create_dataset(
    'unlimited', (2, 3),
    maxshape=(None, None),
    dtype=dt
)

grp = f.create_group('subgroup')
dset[0, 0] = 1
dset[(0, 1)] = 'a'
dset[1, 1:] = 'ab'
dset.resize(dset.shape[0] + 1, axis=0)  # adding a new row
dset[2, 1] = 'abc' * 2

print(f.name, dset.name, dset.shape, dset.dtype)
print(dset[0:4:1])

f.close()

f = h5py.File(my_file, 'r', libver='latest')

f.visit(lambda name: print(name))
print("name: %s, keys: %s, values: %s" % (f.name, f.keys(), f.values()))
group_key = list(f.keys())[0]
data = list(f[group_key])
print(data)

f.close()

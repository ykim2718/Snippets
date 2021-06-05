"""
y, h5py - basic 2.py, 2017.5.30
"""

import h5py
import numpy as np

my_file = 'h5py - basic 2.hdf5'

f = h5py.File(my_file, 'w')
f.create_group('scenario=1')
grp = f.create_group('scenario=1/1')
dt = h5py.special_dtype(vlen=str)
dset = grp.create_dataset('date', (8, ), dtype=dt)
dset[0] = '2016-1-7'
dset[1] = '2016-1-8'
dset[2] = '2016-1-9'
dset = grp.create_dataset('action', (8, ), dtype='S5')  # 'a5' working as well
dset[0] = b'enter'
dset[1] = b'exit'
dset[2] = b'enterxxxxxxxxxxxxx'
dset = grp.create_dataset('price', (8, ), dtype=int)
dset[0] = 100
dset[1] = 110
dset[2] = 120

f.close()


f = h5py.File(my_file, 'r', libver='latest')

f.visit(lambda name: print(name))
print("name: %s, keys: %s, values: %s" % (f.name, f.keys(), f.values()))

for j, (key, value) in enumerate(f.items(), start=1):
    print('/[%d]' % j, key, '=', value, type(value), isinstance(value, h5py.Group))
for j, (key, value) in enumerate(f['scenario=1'].items(), start=1):
    print('/[%d]' % j, key, '=', value, type(value), isinstance(value, h5py.Group))
for j, (key, value) in enumerate(f['scenario=1/1'].items(), start=1):
    print('/[%d]' % j, key, '=', value, type(value), isinstance(value, h5py.Dataset))

key = 'scenario=1/1/date'
print(key, list(f[key]), type(f[key]), isinstance(f[key], h5py.Dataset))

key = 'scenario=1/1/action'
print(key, list(f[key]))

key = 'scenario=1/1/price'
print(key, list(f[key]))

f.close()



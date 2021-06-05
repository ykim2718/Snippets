"""
y, pandas hdf5 - write file with different complevel.py, 2018.9.17, 9.30, 10.1
https://stackoverflow.com/questions/14332193/hdf5-storage-overhead
https://support.hdfgroup.org/HDF5/doc1.6/UG/10_Datasets.html
https://www.systutorials.com/docs/linux/man/1-h5repack/
"""

import pandas as pd
import os

module_name = os.path.basename(__file__)
a_file = module_name[:-3] + '.h5'

report = pd.DataFrame()
frame = pd.DataFrame([1])
# for j in range(9, -1, -1):
for j in range(10):
    k = "complevel=%d" % j
    print(k)
    frame.to_hdf(a_file, key='frame', format='table', complevel=j, complib='zlib')
    report.loc[k, 'h5_size'] = os.path.getsize(a_file)
    b_file = a_file.replace('.h5', ' after_h5repack.h5')
    os.system(r'h5repack.exe -i "{i}" -o "{o}" -l COMPA'.format(i=a_file, o=b_file))
    report.loc[k, 'h5_repack_size'] = os.path.getsize(b_file)
    c_file = a_file.replace('.h5', '.csv')
    frame.to_csv(c_file)
    report.loc[k, 'csv_size'] = os.path.getsize(c_file)

print(pd.read_hdf(a_file, key='frame'))
print(pd.read_hdf(b_file, key='frame'))

print(report)


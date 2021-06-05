"""
y, pandas hdf5 - read write hdf5 (2).py, 2018.9.5, 9.14, 9.16
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.to_hdf.html
https://www.pythonforthelab.com/blog/how-to-use-hdf5-files-in-python/
https://stackoverflow.com/questions/22998859/hdfstore-with-string-columns-gives-issues
"""

import pandas as pd
import os
import datetime as dt
import numpy as np
import h5py

_module_name = os.path.splitext(os.path.basename(__file__))[0]
hdf5_name = "%s.h5" % _module_name

df = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6], 'C': ['seven', 'eight', 'nine']}, index=['a', 'b', 'c'])
# df.reset_index(inplace=True)
# df[df.columns] = df[df.columns].applymap(str)
# df[df.columns] = df[df.columns].astype('category')
df.to_hdf(hdf5_name, key='frame', mode='w', format='table', complevel=9)

df_empty = pd.DataFrame([None])  # 2018.9.16
df_empty.to_hdf(hdf5_name, key='empty_frame', mode='a', format='table', complevel=9)

s = pd.Series([1, 'two', False, None, np.nan, dt.datetime.now()], index=list('abcdef'))
s = s.apply(str)
s.to_hdf(hdf5_name, key='series', mode='a', format='table', complevel=9)

print('frame\n', pd.read_hdf(hdf5_name, 'frame'), end='\n'*2)
print('empty_frame\n', pd.read_hdf(hdf5_name, 'empty_frame'), end='\n'*2)
print('series\n', pd.read_hdf(hdf5_name, 'series'), end='\n'*2)

with h5py.File(hdf5_name, 'r') as f:
    for k in f.keys():
        print(k)



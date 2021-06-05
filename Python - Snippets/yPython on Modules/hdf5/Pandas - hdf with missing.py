"""
y, Python pandas - hdf with missing.py, 2017.5.14


http://pandas.pydata.org/pandas-docs/stable/io.html

"""

import pandas as pd
import numpy as np

df_with_missing = pd.DataFrame({
    'col1': [0, np.nan, 2],
    'col2': [1, np.nan, np.nan],
    'col3': ['ab', 'abc', 'abcde'],
})
print(df_with_missing)

df_with_missing.to_hdf(
    'file.h5',  # file name
    'df_with_missing',  # table name
    format='table',
    mode='w',
    append=False,
    dropna=True,
    data_columns=['col1'],  # ???? looks not working
    min_itemsize={'col3': 3},  # ???? looks not working
    complib='blosc',  # compression method
    complevel=9,  # 0 to max 9, compression level
)

df = pd.read_hdf('file.h5', 'df_with_missing')
df = pd.read_hdf('file.h5', 'df_with_missing', where=['index > 1'])
print(df)

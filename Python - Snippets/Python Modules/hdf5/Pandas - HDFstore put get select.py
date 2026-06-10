"""
y, Pandas - HDFstore put get select.py, 2017.5.30 - 31
"""

import os
import pandas as pd

my_file = 'Pandas - HDFstore put get select.h5'
if os.path.exists(my_file):
    os.remove(my_file)

hdf = pd.HDFStore(my_file)
df = pd.DataFrame([['2017-5-29', 'enter', 529],
                   ['2017-5-29', 'enter', 530]],
                   columns=['date', 'action', 'price'])
key = 's_1/code1/p_1'
hdf.put(key, df, format='table', data_columns=True)
hdf.close()

new_value = '12345689'
df['action'].iloc[0] = new_value[0:5]  # should cut to obey fixed-length string

with pd.HDFStore(my_file) as store:
    store.append(key, df)

with pd.HDFStore(my_file) as store:
    df = store.get(key)
    print(df)

with pd.HDFStore(my_file) as store:
    df = store.select(key, [pd.io.pytables.Term('action', '=', 'enter')])
    print(df)

with pd.HDFStore(my_file) as store:
    df = store.select(key, where='price>529')  # causes 'FutureWarning'
    print(df)


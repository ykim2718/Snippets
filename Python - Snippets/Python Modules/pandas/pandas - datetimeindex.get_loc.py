"""
y, pandas - datetimeindex.get_loc.py, 2017.11.24
"""

import pandas as pd

a = pd.date_range('2017-1-1', '2017-1-31', freq='3D')
print(a)

the_date = pd.Timestamp('2017-1-18')
print('the_date =', the_date)
j = a.get_loc(the_date, method='nearest')
print('nearest =', a[j])
j = a.get_loc(the_date, method='bfill')
print('bfill =', a[j])
j = a.get_loc(the_date, method='ffill')
print('ffill =', a[j])

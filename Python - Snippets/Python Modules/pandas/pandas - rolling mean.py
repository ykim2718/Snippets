"""
y, pandas - rolling mean.py, 2016.4.30, 2017.11.1
"""

import pandas as pd

date1 = '2016-04-25'
date2 = '2016-04-30'
dates = pd.date_range(date1, date2, freq='2d').tolist()
df = pd.DataFrame({'data': range(len(dates))}, index=dates)
df['rmean'] = df['data'].rolling(window=2, center=False).mean()
print(df)
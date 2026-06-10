"""
y, datetime - pd.to_timedelta.py, 2018.9.5
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.to_timedelta.html
"""

import pandas as pd
import datetime as dt

a = dt.datetime(2018, 9, 5, 12, 0, 0)
td = pd.to_timedelta('-1d1h30m')
print(a+td)
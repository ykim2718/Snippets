"""
y, 2020.1.18
pandas - datetimeindex utc.py
"""

import datetime as dt
import pandas as pd

TZ_SEOUL = dt.timezone(dt.timedelta(hours=9))
a = dt.datetime(2020, 1, 2, 3, 4)
b = dt.datetime(2020, 1, 2, 3, 4).replace(tzinfo=TZ_SEOUL)
print(a)
print(b)

c = pd.Series([a, b])
c = c.apply(lambda x: x.replace(tzinfo=TZ_SEOUL))
d = pd.DatetimeIndex(c)
print(d)

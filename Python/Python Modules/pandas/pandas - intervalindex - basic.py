"""
y, 2020.4.29
pandas - intervalindex basic.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.IntervalIndex.html
https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#dateoffset-objects
https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#offset-aliases  << frequency string
"""

import pandas as pd
import datetime as dt

TZ_SEOUL = dt.timezone(dt.timedelta(hours=9), name='Korea/Seoul')
a = pd.interval_range(start=pd.Timestamp('2020-1-1 04:05:06', tzinfo=TZ_SEOUL),
                      end=pd.Timestamp('2020-1-1 12:13:14', tzinfo=TZ_SEOUL),
                      freq='10min')
print(f"a={a}")
print(f"a.size={a.size}")

b = pd.IntervalIndex.from_tuples([
    (pd.Timestamp('2020-1-1 12:13:15', tzinfo=TZ_SEOUL), pd.Timestamp('2020-1-1 12:13:16', tzinfo=TZ_SEOUL)),
    (pd.Timestamp('2020-1-1 12:13:17', tzinfo=TZ_SEOUL), pd.Timestamp('2020-1-1 12:13:18', tzinfo=TZ_SEOUL))
])
# print(f"b={b}")
# print(f"b.size={b.size}")

c = pd.IntervalIndex.from_tuples([
    (pd.Timestamp('2020-1-1 12:13:10', tzinfo=TZ_SEOUL), pd.Timestamp('2020-1-1 12:13:20', tzinfo=TZ_SEOUL)),
])
# print(f"c={c}")
# print(f"c.size={c.size}")

d = b.intersection(c)
print(f"d={d}")
print(f"d.size={d.size}")  # 0 # be careful to use pd.IntervalIndex

e = b.append(c)
print(f"e={e}")
print(f"e.size={e.size}, b.size+c.size={b.size+c.size}")  # 3, 3
print(f"e.is_overlapping={e.is_overlapping}")  # True

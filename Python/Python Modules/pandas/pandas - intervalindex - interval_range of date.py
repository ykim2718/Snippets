"""
y, 2021.2.9
pandas - intervalindex - interval range of date.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.interval_range.html#pandas.interval_range
"""

import pandas as pd

"""
2021년 1월
Sun Mon Tue Wed Thu Fri Sat
 24  25  26  27  28  29  30
 31   1   2   3   4   5   6
  7   8   9  10  11  12  13
"""


start = pd.Timestamp('2021-1-26')
stop = pd.Timestamp('2021-2-9')
intervals = pd.interval_range(start=start, end=stop, freq='3B', closed='left')
print(f"intervals.is_overlapping={intervals.is_overlapping}")
for interval in intervals:
    print(interval, interval.left, interval.right, interval.closed, interval.length)
"""
[2021-01-26, 2021-01-29)
[2021-01-29, 2021-02-03)
[2021-02-03, 2021-02-08)
"""

index = pd.date_range(start=pd.Timestamp('2021-1-1'), end=pd.Timestamp('2021-2-15'), freq='1d')
a = pd.Series(list(range(index.size)), index=index)
for interval in intervals:
    mask = (interval.left <= a.index) & (a.index < interval.right)
    print(a[mask])
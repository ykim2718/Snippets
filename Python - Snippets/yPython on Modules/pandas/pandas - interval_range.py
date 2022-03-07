"""
y, 2022.3.7
pandas - interval_range.py
https://pandas.pydata.org/docs/reference/api/pandas.interval_range.html#
"""


import pandas as pd

query_days = 10
start_date = pd.Timestamp('2020-1-1', tz='Asia/Seoul')
stop_date = pd.Timestamp('2020-3-31', tz='Asia/Seoul')

intervals = pd.interval_range(start=start_date, end=stop_date, freq=f"{query_days}B")
if intervals[-1].right < stop_date:
    end_interval = pd.IntervalIndex.from_breaks([intervals[-1].right, stop_date])
    intervals = intervals.append(end_interval)
for j, interval in enumerate(intervals, start=1):
    print(j, interval)


"""
1 (2020-01-01, 2020-01-15]
2 (2020-01-15, 2020-01-29]
3 (2020-01-29, 2020-02-12]
4 (2020-02-12, 2020-02-26]
5 (2020-02-26, 2020-03-11]
6 (2020-03-11, 2020-03-25]
7 (2020-03-25, 2020-03-31]  << broken end_interval
"""


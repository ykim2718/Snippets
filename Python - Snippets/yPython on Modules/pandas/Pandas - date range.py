"""
y, Pandas - date range.py, 2016.6.22 - 23
"""

import pandas as pd
import datetime as dt
import operator


def get_biz_date_list(start_date, stop_date):
    dates = pd.date_range(start_date, stop_date, freq='D')
    if len(dates) == 0: return []
    print(dates, type(dates), len(dates))
    dates = dates[dates.dayofweek < 5]
    print(dates, type(dates), len(dates))

    # date_series = pd.Series(index=dates)
    dates = list(dates)
    # d = list(map(operator.sub, dates[1:], dates[:-1]))
    d = list(map(lambda x, y: (x - y).days, dates[1:], dates[:-1]))
    print(d, type(d), len(d))

    periods = []
    start = end = []
    for i, j in enumerate(d):
        if start == []:
            start = dates[i]
        if j == 1:
            continue
        elif j > 1:
            end = dates[i]
            periods.append((start, end))
            start = end = []
    if start == []:
        start = dates[-1]
    end = dates[-1]
    periods.append((start, end))

    return periods  # list of tuples


if __name__ == '__main__':

    start = '2016-6-3'
    end = dt.datetime(2016, 6, 20)
    periods = get_biz_date_list(start, end)
    print(type(periods), len(periods), type(periods[0]), len(periods[0]))
    for i, span in enumerate(periods):
        print(i, span)

"""
y, pandas - custom biz day, 2018.10.27
https://stackoverflow.com/questions/42789645/how-to-find-business-days-between-dates-with-pandas-cday
https://docs.scipy.org/doc/numpy-1.10.1/reference/generated/numpy.busday_count.html
https://pandas.pydata.org/pandas-docs/stable/timeseries.html
https://pandas.pydata.org/pandas-docs/stable/timeseries.html#timeseries-custombusinessdays
"""

import pandas as pd
import numpy as np
import datetime as dt

weekmask = 'Mon Wed Fri Sat'
holidays = [dt.datetime(2017, 3, 6), dt.datetime(2017, 3, 11)]

my_calendar = pd.tseries.offsets.CustomBusinessDay(holidays=holidays, weekmask=weekmask)
c = np.busday_count(dt.datetime(2017, 3, 5), dt.datetime(2017, 3, 12),
                    weekmask=my_calendar.weekmask, holidays=my_calendar.holidays)
print(c)
index = pd.date_range(dt.datetime(2017, 3, 5), dt.datetime(2017, 3, 12), freq=None)  # freq='D'
print(index)
index = pd.date_range(dt.datetime(2017, 3, 5), dt.datetime(2017, 3, 12), freq=my_calendar)
print(index)
print(len(index))


from pandas.tseries.holiday import USFederalHolidayCalendar
bday_us = CustomBusinessDay(calendar=USFederalHolidayCalendar())
print(bday_us)

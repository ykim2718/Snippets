"""
y, Pandas - weekend days.py, 2018.2.11
https://pandas.pydata.org/pandas-docs/stable/timeseries.html#timeseries-offset-aliases
"""

from pandas.tseries.holiday import Holiday, AbstractHolidayCalendar
import datetime as dt
import pandas as pd

start, stop = dt.date(2018, 2, 1), dt.date(2018, 2, 28)

"""
class ExampleCalendar(AbstractHolidayCalendar):

    rules = [
        Holiday('Sat', month=1, day=1, days_of_week=(5, 6)),
        ]


cal = ExampleCalendar()

a = cal.holidays(dt.date(2018, 2, 1), dt.date(2018, 2, 28))
print(a)
"""

sats = pd.date_range(start=start, end=stop, freq='W-SAT')
suns = pd.date_range(start=start, end=stop, freq='W-SUN')
weekends = sats.append(suns).sort_values()
print(weekends)
print(weekends.to_pydatetime())

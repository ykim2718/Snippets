"""
y, 2023.3.2
pandas - calendar - us holiday (2).py
https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html?highlight=holiday#timeseries-holiday
https://towardsdatascience.com/us-market-bank-holidays-pandas-fbb15c693fcc
"""

from pandas.tseries.holiday import USFederalHolidayCalendar
import pandas as pd

now = pd.Timestamp.now()
year_first = now - pd.offsets.YearBegin()
year_last = now + pd.offsets.YearEnd()
year_first = year_first.date()
year_last = year_last.date()
print(f"{year_first=}")
print(f"{year_last=}")

cal = USFederalHolidayCalendar()
holidays = cal.holidays(start=str(year_first), end=str(year_last), return_name=True)
print(f"{holidays=}")

bz_dates = pd.date_range(start=str(year_first), end=str(year_last), freq=pd.offsets.CDay(calendar=cal))
print(f"{bz_dates=}")

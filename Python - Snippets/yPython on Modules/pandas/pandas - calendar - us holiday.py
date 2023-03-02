"""
y, 2019.3.12; 2023.3.2
pandas - calendar - us holiday.py.py
https://stackoverflow.com/questions/33094297/create-trading-holiday-calendar-with-pandas
https://pandas.pydata.org/pandas-docs/stable/timeseries.html#timeseries-offset-aliases
"""

from pandas.tseries.holiday import AbstractHolidayCalendar, Holiday, nearest_workday, \
    USMartinLutherKingJr, USPresidentsDay, GoodFriday, USMemorialDay, \
    USLaborDay, USThanksgivingDay
import pandas as pd

now = pd.Timestamp.now()
year_first = now - pd.offsets.YearBegin()
year_last = now + pd.offsets.YearEnd()
year_first = year_first.date()
year_last = year_last.date()
print(f"{year_first=}")
print(f"{year_last=}")


class USTradingCalendar(AbstractHolidayCalendar):
    rules = [
        Holiday('NewYearsDay', month=1, day=1, observance=nearest_workday),
        USMartinLutherKingJr,
        USPresidentsDay,
        GoodFriday,
        USMemorialDay,
        Holiday('USIndependenceDay', month=7, day=4, observance=nearest_workday),
        USLaborDay,
        USThanksgivingDay,
        Holiday('Christmas', month=12, day=25, observance=nearest_workday)
    ]


cal = USTradingCalendar()
holidays = cal.holidays(year_first, year_last, return_name=True)
print(f"{holidays=}")

"""
year_first=datetime.date(2023, 1, 1)
year_last=datetime.date(2023, 12, 31)
holidays=2023-01-02                   NewYearsDay
2023-01-16    Martin Luther King Jr. Day
2023-02-20                Presidents Day
2023-04-07                   Good Friday
2023-05-29                  Memorial Day
2023-07-04             USIndependenceDay
2023-09-04                     Labor Day
2023-11-23                  Thanksgiving
2023-12-25                     Christmas
dtype: object
"""
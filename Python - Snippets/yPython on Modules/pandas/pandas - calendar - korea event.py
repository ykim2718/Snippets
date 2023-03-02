"""
y, 2023.3.2
pandas - calendar - korea event.py
"""

from pandas.tseries.holiday import AbstractHolidayCalendar, Holiday, nearest_workday, previous_workday
from pandas.tseries.offsets import DateOffset
from dateutil.relativedelta import MO, TU, WE, TH, FR, SA, SU
import pandas as pd

now = pd.Timestamp.now()
year_first = now - pd.offsets.YearBegin()
year_last = now + pd.offsets.YearEnd()
year_first = year_first.date()
year_last = year_last.date()
print(f"{year_first=}")
print(f"{year_last=}")


class KoreaEventCalendar(AbstractHolidayCalendar):
    rules = [
        Holiday('수출통계발표', month=j, day=1, observance=nearest_workday) for j in range(1, 13)
    ] + [
        Holiday('네마녀의날', month=j, day=1, offset=DateOffset(weekday=TH(2))) for j in [3, 6, 9, 12]
    ] + [
        Holiday('연말휴장일', month=1, day=1, observance=previous_workday)
    ]

    def events(self, *args, **kwargs):
        return self.holidays(*args, **kwargs)


cal = KoreaEventCalendar()
events = cal.events(year_first, year_last, return_name=True)
print(f"{events=}")

"""
year_first=datetime.date(2023, 1, 1)
year_last=datetime.date(2023, 12, 31)
events=2023-01-02     수출통계발표
2023-02-01     수출통계발표
2023-03-01     수출통계발표
2023-03-09    네 마녀의 날
2023-03-31     수출통계발표
2023-05-01     수출통계발표
2023-06-01     수출통계발표
2023-06-08    네 마녀의 날
2023-06-30     수출통계발표
2023-08-01     수출통계발표
2023-09-01     수출통계발표
2023-09-14    네 마녀의 날
2023-10-02     수출통계발표
2023-11-01     수출통계발표
2023-12-01     수출통계발표
2023-12-14    네 마녀의 날
2023-12-29      연말휴장일
dtype: object
"""
"""
y, 2023.3.2 - 3$
pandas - calendar - korea event.py
"""

from pandas.tseries.holiday import (
    AbstractHolidayCalendar, Holiday, nearest_workday, previous_workday, weekend_to_monday
)
from pandas.tseries.offsets import DateOffset, YearBegin, YearEnd
from dateutil.relativedelta import MO, TU, WE, TH, FR, SA, SU
import pandas as pd

now = pd.Timestamp.now()
year_first = now - pd.offsets.YearBegin()
year_last = now + pd.offsets.YearEnd()
year_first = year_first.date()
year_last = year_last.date()
print(f"{year_first=}")
print(f"{year_last=}")


print(' KoreaEventCalendar0 '.center(64, '-'))


class KoreaEventCalendar0(AbstractHolidayCalendar):

    def __init__(self, rules):
        assert isinstance(rules, list) and rules
        super().__init__(rules=rules)

    def events(self, start=None, stop=None) -> pd.Series:
        return self.holidays(start=start, end=stop, return_name=True)


rules = [
    Holiday('수출통계발표', month=j, day=1, observance=weekend_to_monday) for j in range(1, 13)
] + [
    Holiday('네마녀의날', month=j, day=1, offset=DateOffset(weekday=TH(2))) for j in [3, 6, 9, 12]
] + [
    # Holiday('연말휴장일', month=1, day=1, observance=previous_workday)
    Holiday('연말휴장일', month=12, day=1, observance=YearEnd())
]


cal = KoreaEventCalendar0(rules)
events = cal.events(year_first, year_last)
print(f"{type(events)=}, events=\n{events}")

"""
events=2023-01-02    수출통계발표
2023-02-01    수출통계발표
2023-03-01    수출통계발표
2023-03-09     네마녀의날
2023-03-31    수출통계발표
2023-05-01    수출통계발표
2023-06-01    수출통계발표
2023-06-08     네마녀의날
2023-06-30    수출통계발표
2023-08-01    수출통계발표
2023-09-01    수출통계발표
2023-09-14     네마녀의날
2023-10-02    수출통계발표
2023-11-01    수출통계발표
2023-12-01    수출통계발표
2023-12-14     네마녀의날
2023-12-31     연말휴장일
dtype: object
"""


print(' KoreaEventCalendar1 '.center(64, '-'))


class KoreaEventCalendar1(AbstractHolidayCalendar):

    def __init__(self, rules):
        assert isinstance(rules, dict) and rules
        a = []
        for event_name, event_para in self.event_generator(rules):
            a.append(Holiday(event_name, **event_para))
        super().__init__(rules=a)

    @staticmethod
    def event_generator(event_dict):
        for event_name, event_param in event_dict.items():
            if p := event_param.get('offset', None):
                if p in ['YearFirst()', 'YearEnd()'] or p.startswith('DateOffset'):
                    event_param['offset'] = eval(p, globals())
                else:
                    raise AssertionError(f"invalid offset={p}")
            if p := event_param.get('observance', None):
                if p in ['weekend_to_monday']:
                    event_param['observance'] = eval(p, globals())
                else:
                    raise AssertionError(f"invalid observance={p}")
            for key, value in event_param.items():
                if isinstance(value, list):
                    for v in value:
                        yield event_name, event_param | {key: v}
                    break
            else:
                yield event_name, event_param

    def events(self, start=None, stop=None) -> pd.Series:
        return self.holidays(start=start, end=stop, return_name=True)


d = {
    "_id": "Korea",
    "수출통계발표": {
        "month": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
        "day": 1,
        "observance": "weekend_to_monday"
    },
    "네마녀의날": {
        "month": [3, 6, 9, 12],
        "day": 1,
        "offset": "DateOffset(weekday=TH(2))"
    },
    "연말휴장일": {
        "month": 1,
        "day": 1,
        "offset": "YearEnd()"
    }
}
d.pop('_id')

cal = KoreaEventCalendar1(d)
events = cal.events(year_first, year_last)
print(f"{type(events)=}, events=\n{events}")

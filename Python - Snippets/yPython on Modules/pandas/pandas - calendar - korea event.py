"""
y, 2023.3.2 - 3$ - 5
pandas - calendar - korea event.py
"""

from pandas.tseries.holiday import (
    AbstractHolidayCalendar, Holiday, nearest_workday, previous_workday, weekend_to_monday
)
from pandas.tseries.offsets import DateOffset, YearBegin, YearEnd, QuarterBegin, QuarterEnd, MonthBegin, MonthEnd
from dateutil.relativedelta import MO, TU, WE, TH, FR, SA, SU
import pandas as pd
import datetime
import functools


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

offset_methods = ['MonthEnd()', 'YearEnd()']
observance_methods = ['weekend_to_monday', 'two_previous_workday', 'three_previous_workday']


class KoreaEventCalendar1(AbstractHolidayCalendar):

    def __init__(self, events):
        assert isinstance(events, list) and events
        self.descriptions = dict()
        rules = []
        for event in events:
            for name, description, parameters in self.event_generator(event):
                rules.append(Holiday(name, **parameters))
                self.descriptions[name] = description
        super().__init__(rules=rules)

    @staticmethod
    def event_generator(event):
        assert isinstance(event, dict)
        _id = event.pop('_id')
        name = _id['event']
        description = event.pop('description', '')
        if p := event.get('offset', None):
            if p in offset_methods or p.startswith('DateOffset'):
                event['offset'] = eval(p, globals())
            else:
                raise AssertionError(f"invalid offset={p}")
        if p := event.get('observance', None):
            if p in observance_methods:
                event['observance'] = eval(p, globals())
            else:
                raise AssertionError(f"invalid observance={p}")
        for key, value in event.items():
            if isinstance(value, list):
                for v in value:
                    yield name, description, event | {key: v}
                break
        else:
            yield name, description, event

    def events(self, start=None, stop=None) -> pd.DataFrame:
        names = self.holidays(start=start, end=stop, return_name=True)
        assert isinstance(names, pd.Series), f"expected pd.Series but got {names=}"
        names.name = 'name'
        descriptions = names.apply(lambda name: self.descriptions[name])
        descriptions.name = 'description'
        a = pd.concat([names, descriptions], axis=1)
        return a


def find_previous_workday(dt: datetime, offset_days=1) -> datetime:
    """ y, 2023.3.5 """

    assert isinstance(offset_days, int) and offset_days >= 1

    def _skip_weekend(dt):
        while dt.weekday() > 4:  # Mon-Fri are 0-4
            dt -= datetime.timedelta(days=1)
        return dt

    dt = _skip_weekend(dt)
    dt -= datetime.timedelta(days=offset_days)
    dt = _skip_weekend(dt)
    return dt


two_previous_workday = functools.partial(find_previous_workday, offset_days=2)
three_previous_workday = functools.partial(find_previous_workday, offset_days=3)


a = [
    {
        "_id": {"country": "Korea", "event": "수출통계발표"},
        "description": "산업통상자원부 수출입동향 발표 (매달 1일)",
        "month": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
        "day": 1,
        # "observance": "weekend_to_monday"
    },
    {
        "_id": {"country": "Korea", "event": "네마녀의날"},
        "description": "주가지수 선물과 옵션 그리고 개별주식 선물과 옵션의 만기일",
        "month": [3, 6, 9, 12],
        "day": 1,
        "offset": "DateOffset(weekday=TH(2))"
    },
    {
        "_id": {"country": "Korea", "event": "대주주기준일"},
        "description": "대주주 양도차익 과세기준일",
        "month": 12,
        "day": 31,
        "observance": "three_previous_workday"
    },
    {
        "_id": {"country": "Korea", "event": "배당락일"},
        "description": "배당기준일 다음날 (하락예상)",
        "month": 12,
        "day": 31,
        "observance": "two_previous_workday"
    }
]

cal = KoreaEventCalendar1(a)
events = cal.events(year_first, year_last)
print(f"{type(events)=}, events=\n{events}")

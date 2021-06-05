"""
y, 2020.1.16
pytz - timezone.py
"""

import pytz
import datetime as dt

TZ_SEOUL_BY_PYTZ = pytz.timezone('Asia/Seoul')
TZ_SEOUL_BY_DATETIME = dt.timezone(dt.timedelta(hours=9))

a_time = dt.datetime(2020, 1, 16, 12, 12, 12)
print(f"a_time={a_time}")
print(TZ_SEOUL_BY_PYTZ.localize(a_time))
print(a_time.replace(tzinfo=TZ_SEOUL_BY_DATETIME))
a_time = dt.datetime(2020, 1, 16, 12, 12, 12, tzinfo=TZ_SEOUL_BY_DATETIME)
print(f"a_time={a_time}")
print('TZ_SEOUL_BY_PYTZ.localize(a_time) >> ValueError: Not naive datetime (tzinfo is already set)')
print(a_time.replace(tzinfo=TZ_SEOUL_BY_DATETIME))

"""
a_time=2020-01-16 12:12:12
2020-01-16 12:12:12+09:00
2020-01-16 12:12:12+09:00
a_time=2020-01-16 12:12:12+09:00
TZ_SEOUL_BY_PYTZ.localize(a_time) >> ValueError: Not naive datetime (tzinfo is already set)
2020-01-16 12:12:12+09:00
"""

"""
y, 2020.3.18
datetime - replace timezone.py
"""

import datetime as dt

now = dt.datetime.now()
print(now, '>>', now.tzinfo)
TZ_SEOUL = dt.timezone(dt.timedelta(hours=9))
now_tz = now.replace(tzinfo=TZ_SEOUL)
print(now_tz, '>>', now_tz.tzinfo)

import pandas as pd

now_tz_pd = pd.Timestamp(now_tz)
print(now_tz_pd, '>>', now_tz_pd.tzinfo)

'''
2020-03-19 20:54:47.682905 >> None
2020-03-19 20:54:47.682905+09:00 >> UTC+09:00
2020-03-19 20:54:47.682905+09:00 >> UTC+09:00
'''

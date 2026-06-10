"""
y, 2020.4.22
pandas - applymap.py
"""

import pandas as pd
import datetime as dt

TZ_SEOUL = dt.timezone(dt.timedelta(hours=9), name='Korea/Seoul')
TZ_NEWYORK = dt.timezone(dt.timedelta(hours=-4), name='USA/Newyork')

a = pd.DataFrame([dt.datetime.now(tz=TZ_SEOUL)])
print('a=', a.loc[0, 0].tzinfo)  # Korea/Seoul
b = a.applymap(lambda x: x.replace(tzinfo=TZ_NEWYORK))
print('a=', a.loc[0, 0].tzinfo)  # Korea/Seoul
print('b=', b.loc[0, 0].tzinfo)  # USA/Newyork
b = a.applymap(lambda x: x.replace(tzinfo=None))
print('a=', a.loc[0, 0].tzinfo)  # Korea/Seoul
print('b=', b.loc[0, 0].tzinfo)  # None

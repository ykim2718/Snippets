"""
y, datetime - utcnow.py, 2019.9.4
"""

import datetime as dt

KST = dt.timezone(dt.timedelta(hours=9))
print(dt.datetime.now())
print(dt.datetime.now(tz=KST))
print(dt.datetime.now(tz=dt.timezone.utc))
print(dt.datetime.utcnow())

"""
2019-09-04 19:14:11.222257
2019-09-04 19:14:11.222257+09:00
2019-09-04 10:14:11.222257+00:00
2019-09-04 10:14:11.222257
"""

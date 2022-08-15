"""
y, 2022.8.15
exchange_calendars - basic.py
https://iamaman.tistory.com/3542
https://github.com/gerrymanoim/exchange_calendars
"""

import exchange_calendars as xcals
import datetime as dt
import pandas as pd

xkrx = xcals.get_calendar('XKRX')
print(xkrx.is_session('2022-03-09'))  # 대한민국 제20대 대통령 선거일
print(xkrx.is_session(dt.date.today().strftime('%Y-%m-%d')))  # 오늘은 개장일인지 확인
print(xkrx.next_open(pd.Timestamp.today()))  # 다음 개장일은 언제인지 확인

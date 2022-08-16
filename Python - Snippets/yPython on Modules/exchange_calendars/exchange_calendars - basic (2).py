"""
y, 2022.8.16
exchange_calendars - basic (2).py
https://iamaman.tistory.com/3542
https://github.com/gerrymanoim/exchange_calendars
"""

import exchange_calendars as xcals
import pandas as pd

xkrx = xcals.get_calendar('XKRX')
print(f"{xkrx.name=}")
print(f"{xkrx.has_break=}")
print(f"{xkrx.first_session=}")
print(f"{xkrx.last_session=}")
print(f"{xkrx.first_minute.tz_convert(xkrx.tz)=}")
print(f"{xkrx.last_minute.tz_convert(xkrx.tz)=}")
print(f"{xkrx.first_session_open.tz_convert(xkrx.tz)=}")
print(f"{xkrx.last_session_close.tz_convert(xkrx.tz)=}")
print(xkrx.sessions_in_range('2022-03-01', '2022-03-10'))  # 3/9 Presidential electrion day
print(xkrx.sessions_in_range('2022-06-01', '2022-06-10'))  # 6/1 Local electron day

a = xkrx.schedule.loc[['2022-08-16']]
print(a.applymap(lambda t: t.tz_convert(xkrx.tz)))

print(xkrx.is_session(pd.Timestamp.now(tz=xkrx.tz).date()))
print(xkrx.is_trading_minute(pd.Timestamp.now(tz=xkrx.tz)))
print(xkrx.next_open(pd.Timestamp.today(tz=xkrx.tz)))  # 다음 개장일은 언제인지 확인

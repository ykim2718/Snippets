"""
y, 2022.8.15; 2024.1.28
exchange_calendars - basic.py
https://iamaman.tistory.com/3542
https://github.com/gerrymanoim/exchange_calendars
"""

import exchange_calendars as xcals
import datetime as dt
import pandas as pd

krx = xcals.get_calendar('XKRX')
print(f"{krx.is_session(dt.date.today().strftime('%Y-%m-%d'))=}")  # 개장일 여부
print(f"{krx.is_session('2022-03-09')=} << 대한민국 제20대 대통령 선거일")
print(f"{krx.is_trading_minute(pd.Timestamp('2024-1-2 09:59:00', tz='Asia/Seoul'))=} << 연초개장일 개장시간 10시")
print(f"{krx.is_trading_minute(pd.Timestamp('2024-1-2 10:00:00', tz='Asia/Seoul'))=} << 연초개장일 개장시간 10시")
print(f"{krx.is_trading_minute('2023-11-16 09:59:00')=} << 2023학년도 대학수학능력시험일 개장시간 10시")
print(f"{krx.is_trading_minute('2023-11-16 10:00:00')=} << 2023학년도 대학수학능력시험일 개장시간 10시")  # False << BUG
print(f"{krx.is_trading_minute('2024-11-14 09:59:00')=} << 2024학년도 대학수학능력시험일 개장시간 10시")
print(f"{krx.is_trading_minute('2024-11-14 10:00:00')=} << 2024학년도 대학수학능력시험일 개장시간 10시")  # False << BUG
print(f"{krx.first_minute=}")
print(f"{krx.next_open('2022-03-08')=}")  # 다음 개장일
print(f"{krx.next_open(pd.Timestamp.today())=}")  # 다음 개장일


"""
y, 2024.1.11
pandas_market_calendars - basic.py
https://pandas-market-calendars.readthedocs.io/en/latest/index.html
    pip install pandas_market_calendars
https://pandas-market-calendars.readthedocs.io/en/latest/usage.html
"""

# import sys
# sys.path.append("../")
from datetime import time
import pandas as pd
import pandas_market_calendars as mcal

# https://stackoverflow.com/questions/49188960/how-to-show-all-columns-names-on-a-large-pandas-dataframe
pd.options.display.max_columns = None

calendar_names = sorted(mcal.get_calendar_names())
print(f"{calendar_names=}")


nyse = mcal.get_calendar('NYSE')
print(f"{nyse.tz.zone=}")
print(f"{nyse.regular_market_times=}")
extended = nyse.schedule(start_date='2023-11-03', end_date='2023-11-10', start="pre", end="post")
print(f"nyse {extended=}")
"""
nyse extended=                                 pre               market_open  \
2023-11-03 2023-11-03 08:00:00+00:00 2023-11-03 13:30:00+00:00   
2023-11-06 2023-11-06 09:00:00+00:00 2023-11-06 14:30:00+00:00   
"""


xkrx = mcal.get_calendar('XKRX')  # KOREA
print(f"{xkrx.tz.zone=}")
print(f"{xkrx.regular_market_times=}")
extended = xkrx.schedule(start_date='2024-1-1', end_date='2024-01-05')
print(f"xkrx {extended=}")
# FIXME !!! 2024/1/2 개장일의 개장시간이 10시였음에도 market_open=2024-01-02 00:00:00+00:00 임. 틀림 !!!!
#   TradingHours.com에서는 irregular scheudle open 10:00am - 3:30pm 이라고 정확히 알고 있음.
"""
xkrx extended=                         market_open               break_start  \
2024-01-02 2024-01-02 00:00:00+00:00 2024-01-02 03:00:00+00:00   
2024-01-03 2024-01-03 00:00:00+00:00 2024-01-03 03:00:00+00:00   
"""
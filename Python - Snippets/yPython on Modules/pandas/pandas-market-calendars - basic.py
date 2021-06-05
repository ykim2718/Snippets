"""
y, pandas-market-calendars - basic.py, 2019.3.12
https://stackoverflow.com/questions/33094297/create-trading-holiday-calendar-with-pandas
https://pypi.org/project/pandas-market-calendars/
"""

import pandas_market_calendars as mcal

# Create a calendar
nyse = mcal.get_calendar('NYSE')

# Show available calendars
print(mcal.get_calendar_names())

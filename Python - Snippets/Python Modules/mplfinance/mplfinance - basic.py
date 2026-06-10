"""
y, 2022.7.12
mplfinance - basic.py
https://github.com/matplotlib/mplfinance
"""


import mplfinance as mpf
import pandas as pd


daily = pd.read_csv('AAPL.csv')
daily = daily.set_index('Date')
daily.index = pd.to_datetime(daily.index)
daily = daily.iloc[-50:]

mpf.plot(daily, type='candle', mav=(5, 10, 20),volume=True)
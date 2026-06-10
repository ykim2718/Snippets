"""
y, 2022.7.31
pandas_datareader - oecd.py
https://pandas-datareader.readthedocs.io/en/latest/
https://pydata.github.io/pandas-datareader/readers/index.html
    Data Readers
        AlphaVantage
        Federal Reserve Economic Data (FRED)
        Fama-French Data (Ken French’s Data Library)
        Bank of Canada
        Econdb
        Enigma
        Eurostat
        The Investors Exchange (IEX)
        Moscow Exchange (MOEX)
        NASDAQ
        Naver Finance
        Organisation for Economic Co-operation and Development (OECD)
        Quandl
        Stooq.com
        Tiingo
        Thrift Savings Plan (TSP)
        World Bank
        Yahoo Finance
"""


import pandas_datareader as pdr


# https://stats.oecd.org/
#   Data by theme/Monthly Economic Indicators/Composite leading Indicators/Composite Leading Indicators (MEI)/MEI
r = pdr.oecd.OECDReader('MEI', '2022-07-01', '2022-07-31')
"""
requests.exceptions.ReadTimeout: HTTPSConnectionPool(host='stats.oecd.org', port=443): Read timed out. (read timeout=30)
"""
a = r.read()
print(a.tail())

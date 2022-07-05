"""
y, 2022.7.5
pandas_datareader - fred.py
"""


import pandas_datareader as pdr
import datetime as dt


start_date = dt.datetime(2020, 1, 1)
stop_date = dt.datetime(2022, 12, 31)
a = pdr.data.DataReader('GDP', 'fred', start_date, stop_date)
print(a.tail())

"""
                  GDP
DATE                 
2021-01-01  22038.226
2021-04-01  22740.959
2021-07-01  23202.344
2021-10-01  24002.815
2022-01-01  24386.734
"""

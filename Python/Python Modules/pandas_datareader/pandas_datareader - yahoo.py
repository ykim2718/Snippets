"""
y, 2022.7.5
pandas_datareader - yahoo.py
https://pandas-datareader.readthedocs.io/en/latest/
"""


import pandas_datareader as pdr


a = pdr.get_data_yahoo('005930.KS', '2022-07-01', '2022-07-31')
print(a.tail())

"""
             High    Low   Open  Close    Volume  Adj Close
Date                                                       
2022-07-01  57500  55900  56900  56200  24982097      56200
2022-07-04  57400  55700  56100  57100  17807126      57100
2022-07-05  58200  57200  57600  57200  14059216      572004
"""

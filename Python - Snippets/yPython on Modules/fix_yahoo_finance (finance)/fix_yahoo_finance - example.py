"""
y, fix_yahoo_finance - example.py, 2018.7.21
https://www.quora.com/Using-Python-whats-the-best-way-to-get-stock-data
"""

import matplotlib.pyplot as plt
import fix_yahoo_finance as yf
data = yf.download('AAPL', '2016-01-01', '2018-01-01')
print(data.head())
data.to_csv('aapl.csv')
data.Close.plot()
plt.show()
"""
y, pandas - index of date range.py, 2018.10.27
https://jakevdp.github.io/PythonDataScienceHandbook/03.11-working-with-time-series.html
"""

import pandas as pd

index = pd.date_range('2015-07-03', periods=8, freq='B')
index = index.append(pd.date_range('2018-10-27', periods=8, freq='H'))
print(index)

index = pd.period_range('2015-07', periods=8, freq='M')
print(index)

index = pd.timedelta_range(0, periods=10, freq='H')
print(index)

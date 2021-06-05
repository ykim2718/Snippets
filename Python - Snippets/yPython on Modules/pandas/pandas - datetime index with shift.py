"""
y, pandas - datetime index with shift.py, 2017.11.1
"""

import pandas as pd

dates = pd.date_range('2017-11-1', '2017-11-10', freq='2d').tolist()
frame = pd.DataFrame({'data': range(len(dates))}, index=dates)
print(frame)
frame.index = frame.index.shift(1, freq='1d')
print(frame)
"""
y, pandas - dataframe from series.py, 2017.11.2
"""

import pandas as pd

series = pd.Series([0, 1, 2], index=list('abc'))
frame = pd.DataFrame(series)
print(frame)
print(type(frame))

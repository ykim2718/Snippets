"""
y, Pandas - how to find first element index.py, 2018.2.17

"""

import pandas as pd

series = pd.Series([1, 7, 0, 7, 5], index=list('abcde'))
series = series[series == 7]
j = series.index[0]
print('index by series.index[0]:', j)

j = (series == 7).argmax()
print('index by (series == 7).argmax():', j)

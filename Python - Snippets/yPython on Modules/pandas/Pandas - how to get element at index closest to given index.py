"""
y, Pandas - how to get element at index closest to given index.py, 2018.2.19
pandas 0.22.0 documentation >> API Reference >> pandas.index >> pandas.Index.get_loc
    https://pandas.pydata.org/pandas-docs/stable/generated/pandas.Index.get_loc.html
"""

import pandas as pd

series = pd.Series(list('abcd'), index=[-1, 1, 3, 4])
print(series)

print('loc =', series.index.get_loc(2, method='ffill'))
# print('loc =', series.index.get_loc(-2, method='ffill'))  #<<< KeyError: -2
print('loc =', series.index.get_loc(5, method='ffill'))

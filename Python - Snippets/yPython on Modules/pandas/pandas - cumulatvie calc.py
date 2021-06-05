"""
y, pandas - cumulatvie calc.py, 2017.11.14, 11.20
"""

import pandas as pd
import numpy as np

series = pd.Series([1, 2, 4, 8])

print('>> y, 2017.11.14')

s = 'series.cumprod()'
print(s, '-' * 8, '\n', eval(s))

s = 'series.cumsum()'
print(s, '-' * 8, '\n', eval(s))

s = 'series.cummax()'
print(s, '-' * 8, '\n', eval(s))

s = 'series.cummin()'
print(s, '-' * 8, '\n', eval(s))


print('>> y, 2017.11.20')
frame = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [4, 5, 6],
    'c': [7, 8, 9],
}, index=[0, 1, 2])

# frame[['sum(a)', 'sum(b)']] = pd.expanding_apply((frame[['a', 'c']], sum))
frame[['sum(a)', 'sum(b)']] = frame[['a', 'c']].expanding().apply(sum)
frame['stdev.p(a)'] = frame['a'].expanding().apply(np.std)  # stdev.p() of excel
frame['stdev.s(a)'] = frame['a'].expanding().apply(np.std, kwargs=dict(ddof=1))  # stdev.s() of excel
print(frame)



"""
y, pandas - compare series elementwise.py, 2017.11.6
"""

import pandas as pd

index = list('abc')
a = pd.Series([0, 1, 2], index=index)
b = pd.Series([2, 1, 0], index=index)
for exp in ['a.ge(b)', 'a.le(b)',
            'a.gt(b)', 'a.lt(b)',
            'a.eq(b)', 'a.ne(b)']:
    print(exp, '-' * 8, '\n', eval(exp))

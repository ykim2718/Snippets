"""
y, 2022.12.3, pandas - join.py
"""

import pandas as pd

df = pd.DataFrame({'c1': [1, 2, 3]}, index=['r1', 'r2', 'r3'])
dg = pd.DataFrame({'c2': [4, 5, 6]}, index=['r3', 'r4', 'r5'])

f = df.join(dg, how='outer')
print(f)

"""
     c1   c2
r1  1.0  NaN
r2  2.0  NaN
r3  3.0  4.0
r4  NaN  5.0
r5  NaN  6.0
"""
"""
y, 2020.5.12
pandas - update.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.update.html
"""

import pandas as pd
import numpy as np

a = pd.DataFrame(dict(a=[1, 2, 3], b=[4, np.nan, 6]))
b = pd.DataFrame(dict(a=[1, None, pd.NA], b=[np.nan, 5, 60], c=list('ABC')), index=[3, 2, 1])  # must match index
print(f"a={a.shape}\n{a}")
print(f"b={b.shape}\n{b}")
a.update(b)
print(f"a={a.shape}\n{a}")

"""
a=(3, 2)
   a    b
0  1  4.0
1  2  NaN
2  3  6.0
b=(3, 3)
      a     b  c
3     1   NaN  A
2  None   5.0  B
1  <NA>  60.0  C
a=(3, 2)
   a     b
0  1   4.0
1  2  60.0
2  3   5.0
"""

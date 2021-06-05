"""
y, 2020.5.12
pandas - combine_first.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.combine_first.html
"""

import pandas as pd
import numpy as np

a = pd.DataFrame(dict(a=[1, 2, 3], b=[4, np.nan, 6]))
b = pd.DataFrame(dict(a=[1, None, pd.NA], b=[np.nan, 5, 60], c=list('ABC')), index=[3, 2, 1])

print('-' * 32)
print(f"a={a.shape}\n{a}")
print(f"b={b.shape}\n{b}")
c = a.combine_first(b)
print(f"c={c.shape}\n{c}")

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
c=(4, 3)
   a     b    c
0  1   4.0  NaN
1  2  60.0    C
2  3   6.0    B
3  1   NaN    A
"""

b = pd.DataFrame(dict(a=[1, None, pd.NA], b=[np.nan, 5, 60], c=list('ABC')), index=[3, 20, 30])
print('-' * 32)
print(f"a={a.shape}\n{a}")
print(f"b={b.shape}\n{b}")
c = a.combine_first(b)
print(f"c={c.shape}\n{c}")

"""
a=(3, 2)
   a    b
0  1  4.0
1  2  NaN
2  3  6.0
b=(3, 3)
       a     b  c
3      1   NaN  A
20  None   5.0  B
30  <NA>  60.0  C
c=(6, 3)
       a     b    c
0    1.0   4.0  NaN
1    2.0   NaN  NaN
2    3.0   6.0  NaN
3      1   NaN    A
20  None   5.0    B
30  <NA>  60.0    C
"""

a = pd.DataFrame()
print('-' * 32)
print(f"a={a.shape}\n{a}")
print(f"b={b.shape}\n{b}")
c = a.combine_first(b)
print(f"c={c.shape}\n{c}")

"""
a=(0, 0)
Empty DataFrame
Columns: []
Index: []
b=(3, 3)
       a     b  c
3      1   NaN  A
20  None   5.0  B
30  <NA>  60.0  C
c=(3, 3)
       a     b  c
3      1   NaN  A
20  None   5.0  B
30  <NA>  60.0  C
"""

a = pd.DataFrame()
b = pd.DataFrame([1], columns=pd.MultiIndex.from_tuples([('level0', 'level1')]))
print('-' * 32)
print(f"a={a.shape}\n{a}")
print(f"b={b.shape}\n{b}")
c = a.combine_first(b)  # ValueError: cannot join with no overlapping index names
print(f"c={c.shape}\n{c}")

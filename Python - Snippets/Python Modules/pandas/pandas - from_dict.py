"""
y, 2020.10.26
pandas - from_dict.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.from_dict.html
"""

import pandas as pd

a = [dict(a=1), dict(a=2, b=3)]
b = pd.DataFrame.from_dict(a)
print(b)

"""
   a    b
0  1  NaN
1  2  3.0
"""

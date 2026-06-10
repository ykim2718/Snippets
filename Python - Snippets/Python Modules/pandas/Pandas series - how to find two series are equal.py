"""
y, Pandas series - how to find two series are equal.py, 2017.6.2
"""

import pandas as pd

a = pd.Series([0, 1, 2], index=[0, 1, 2])
b = pd.Series([0, 1, 2], index=[0, 1, 2])
c = pd.Series([0, 1, 2], index=[3, 1, 2])
d = pd.Series([3, 1, 2], index=[0, 1, 2])

print(a.equals(b), a.equals(c), a.equals(d))

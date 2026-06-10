"""
y, pandas - min of two series.py, 2019.1.30
https://stackoverflow.com/questions/16989946/creating-an-element-wise-minimum-series-from-two-other-series-in-python-pandas
"""

import pandas as pd

s1 = pd.Series(data=[1, 1, 1], index=[1, 2, 3])
s2 = pd.Series(data=[1, 2, 2, 1], index=[1, 2, 3, 4])

print(pd.concat([s1, s2], axis=1).min(axis=1))
print(pd.DataFrame([s1, s2]).min(axis=0))

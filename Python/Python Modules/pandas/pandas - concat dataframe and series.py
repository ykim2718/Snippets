"""
y, pandas - concat dataframe and series.py, 2018.12.17
"""

import pandas as pd

a = pd.DataFrame([[1, 2, 3], [4, 5, 6]], columns=[0, 1, 2])
b = pd.Series([10, 20, 30], name='series')
c = pd.concat([a, b], axis=1)
print(c)
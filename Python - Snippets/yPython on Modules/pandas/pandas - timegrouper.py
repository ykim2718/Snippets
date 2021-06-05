"""
y, pandas - timegrouper.py, 2019.2.22
https://stackoverflow.com/questions/46328596/python-pandas-rolling-apply-two-time-series-input-into-function
"""

import pandas as pd
import numpy as np

Dates1 = pd.date_range(start='2016-03-31', end='2016-07-31')
data1 = {'A': [np.pi * i * np.random.rand()
               for i in range(1, len(Dates1) + 1)],
         'B': [i * np.random.randn() * 10
               for i in range(1, len(Dates1) + 1)]}
df3 = pd.DataFrame(data=data1, index=Dates1)
print(df3)

df4 = df3.groupby(pd.TimeGrouper(freq='20d')).sum()
print(df4)

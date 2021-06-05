"""
y, Pandas - add last row in place.py, 2017.10.9
"""

import pandas as pd
import numpy as np
import datetime as dt

df = pd.DataFrame(np.random.randint(0, 99, size=(3, 4)), columns=list('abcd'),
                  index=pd.date_range('2017-10-1', periods=3))
print(df)

ds = pd.Series([1, 2, 3, 4], index=df.columns)
# ds = pd.Series([1, 2, 3, 4])

_new_last = 'new_last'
df.loc[_new_last] = ds
print(df)

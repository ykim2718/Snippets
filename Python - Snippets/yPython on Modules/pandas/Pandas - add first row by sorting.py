"""
y, Pandas - add first row by sorting, 2017.10.2
"""

import pandas as pd
import numpy as np
import datetime as dt

df = pd.DataFrame(np.random.randint(0, 99, size=(3, 4)), columns=list('abcd'),
                  index=pd.date_range('2017-10-1', periods=3))
print(df)

# df.set_value(pd.Timestamp('2011-1-1'), df.columns, 200)
min_timestamp_date = pd.Timestamp.min + dt.timedelta(days=1)
df.set_value(min_timestamp_date, df.columns, 200)
df.sort_index(inplace=True)
print(df)

df.drop(min_timestamp_date, inplace=True)
print(df)
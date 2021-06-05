"""
y, Pandas - add first row.py, 2017.9.29
"""

import pandas as pd
import numpy as np

df = pd.DataFrame(np.random.randint(0, 99, size=(3, 4)), columns=list('abcd'))
print(df)

df_new = pd.DataFrame(100, columns=df.columns, index=['new'])
df_new = df_new.append(df)
print(df_new)
print(type(df_new.index[0]), type(df_new.index[-1]))
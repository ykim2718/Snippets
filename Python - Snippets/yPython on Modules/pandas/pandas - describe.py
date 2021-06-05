"""
y, pandas - describe.py, 2017.10.24
"""

import pandas as pd
import numpy as np

df = pd.DataFrame(np.random.randint(0, 99, size=(3, 2)), columns=list('AB'))
print(df)
dd = df.describe()
print(dd)
print(type(dd))
print(dd.loc['mean', 'A'])
"""
y, pandas - append.py, 2019.1.22
"""

import pandas as pd

a = pd.DataFrame({'A': [1], 'B': [2]})
b = pd.DataFrame({'A': [2]})
c = pd.DataFrame({'C': [3]})
print(a.append(b, ignore_index=True, sort=True))
print(a.append(c, ignore_index=True, sort=False))

df = a.append(b, ignore_index=True, sort=False).append(c, sort=False)
print(df)

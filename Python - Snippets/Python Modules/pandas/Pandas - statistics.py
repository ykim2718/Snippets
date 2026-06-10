"""
y, 2016.4.24
"""

import pandas as pd

df = pd.DataFrame({'#1': [0, 2], '#2': [2, 4]}, index=['1st', '2nd'])
df_norm = df / df.max()

print(df_norm)
print(df_norm.mean())

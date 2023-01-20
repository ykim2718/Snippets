"""
y, 2022.3.4, 1.20
pandas - itertuples.py
https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.itertuples.html
"""

import pandas as pd

df = pd.DataFrame({'num_legs': [4, 2], 'num_wings': [0, 2]}, index=['dog', 'hawk'])

for row in df.itertuples(index=False):
    print(row, row.num_legs, row.num_wings)

for row in df.itertuples(name='Animal'):
    print(row, row.Index, row.num_legs, row.num_wings)

"""
y, 2022.3.4, 1.20; 2024.9.22
pandas - itertuples.py
https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.itertuples.html
"""

import pandas as pd

df = pd.DataFrame({'num_legs': [4, 2], 'num_wings': ['zero', 'two']}, index=['dog', 'hawk'])

for row in df.itertuples(index=False):
    print(row, row.num_legs, row.num_wings)

for row in df.itertuples(name='Animal'):
    print(row, row.Index, row.num_legs, row.num_wings)

for index, num_legs, num_wings in df.itertuples():
    print(index, num_legs, num_wings)

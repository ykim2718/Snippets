"""
y, Pandas - drop all duplicates.py, 2016.5.30
Drop all duplicate rows in Python Pandas
http://stackoverflow.com/questions/23667369/drop-all-duplicate-rows-in-python-pandas
"""

import pandas as pd

df = pd.DataFrame({
    'A': ['foo', 'foo', 'foo', 'bar'],
    'B': [2, 1, 1, 1],
    'C': ['A', 'A', 'B', 'A']})
print('before=\n', df)
dg = df.groupby(['A', 'C']).filter(lambda df: df.shape[0] == 1)
print('after=\n', dg)

dg = df.drop_duplicates(subset=['A', 'C'], keep=False)
print('after=\n', dg)

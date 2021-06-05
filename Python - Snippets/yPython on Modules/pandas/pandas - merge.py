"""
y, pandas - merge.py, 2018.6.5
https://pandas.pydata.org/pandas-docs/stable/merging.html
"""

import pandas as pd

left = pd.DataFrame({'key1': ['K0', 'K0', 'K1', 'K2'],
                     'key2': ['K0', 'K1', 'K0', 'K1'],
                     'A': ['A0', 'A1', 'A2', 'A3'],
                     'B': ['B0', 'B1', 'B2', 'B3']})


right = pd.DataFrame({'key1': ['K0', 'K1', 'K1', 'K2'],
                      'key2': ['K0', 'K0', 'K0', 'K0'],
                      'C': ['C0', 'C1', 'C2', 'C3'],
                      'D': ['D0', 'D1', 'D2', 'D3']},
                     index=[10, 20, 30, 40])

print('\nleft\n', left)
print('\nright\n', right)
result = pd.merge(left, right, on=['key1', 'key2'])
print('\nresult\n', result)

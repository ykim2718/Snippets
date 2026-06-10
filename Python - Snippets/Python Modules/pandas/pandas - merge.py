"""
y, pandas - merge.py, 2018.6.5; 2024.7.11
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

print('left=\n', left)
print('right=\n', right)
result = pd.merge(left, right, on=['key1', 'key2'])  # how='inner' as default
print('result=\n', result)

"""
left=
   key1 key2   A   B
0   K0   K0  A0  B0
1   K0   K1  A1  B1
2   K1   K0  A2  B2
3   K2   K1  A3  B3
right=
    key1 key2   C   D
10   K0   K0  C0  D0
20   K1   K0  C1  D1
30   K1   K0  C2  D2
40   K2   K0  C3  D3
result=
   key1 key2   A   B   C   D
0   K0   K0  A0  B0  C0  D0
1   K1   K0  A2  B2  C1  D1
2   K1   K0  A2  B2  C2  D2
"""
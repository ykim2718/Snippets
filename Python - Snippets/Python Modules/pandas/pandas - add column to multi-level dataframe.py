"""
y, pandas - add column to multi-level dataframe.py, 2019.10.9
"""

import pandas as pd

a = pd.DataFrame()
# a.loc[0, ('C', 'D')] = [10, 20]  # KeyError: "['C' 'D'] not in index"
a[('A', 'B')] = [10, 20]
# a.loc[[0, 1], ('C', 'D')] = [10, 20]  # KeyError: "['C' 'D'] not in index"
print('-'*32, '\n', a)

a = pd.DataFrame([0, 0], columns=['Z'])
a[('A', 'B')] = [10, 20]  # Once column is a single level, tuple column places at a single level.
print('-'*32, '\n', a)

a = pd.DataFrame([0, 0], columns=pd.Index([('Z', '')]))
a[('A', 'B')] = [10, 20]
print('-'*32, '\n', a)
print('nlevels=', a.columns.nlevels)  # 2  ???
print(a.loc[0, 'Z'])  # series
print(a.loc[0, ('Z', '')])  # scalar

a = pd.DataFrame([0, 0], columns=pd.Index([('', 'Z')]))
a[('A', 'B')] = [10, 20]
print('-'*32, '\n', a)
print(a[('', 'Z')])

a = pd.DataFrame([[1, 2, 3], [4, 5, 6]], columns=pd.Index([('1st', 'A'), ('1st', 'B'), ('2nd', 'C')]))
a[('A', 'B')] = [10, 20]
a['C'] = [30, 40]
print('-'*32, '\n', a)
# print(a['C'])


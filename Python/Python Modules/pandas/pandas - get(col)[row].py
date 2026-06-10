"""
y, pandas - get(col)[row].py, 2018.4.9
"""

import pandas as pd

print('pd.DataFrame', '-' * 32)

a = pd.DataFrame({'a': [1, 2], 'b': [3, 4]}, index=list('AB'))
print(a)
print(a.get('b')[1])  # read
a.get('b')[1] = 11  # write
print(a)
a.get('b')[[0, 1]] = 22  # write
print(a)
a.get('b')[['A', 'B']] = 33  # write
# a.get('b')[['C']] = 44  # write, not working
print(a)
print(a.get(['b']))
# print(a.get(['b'])['A'])  # not working
# print(a.get(['b'])['A', 'B'])  # not working

print('pd.Series', '-' * 32)

a = pd.Series([1, 2], index=list('AB'))
print(a)
print(a.get('A'))
# a.get('A)') = 11  # not working
a.put(0, 11)  # positional index, not adding but replacing
print(a)

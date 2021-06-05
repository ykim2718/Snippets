"""
y, 2021.2.8
pandas - how to append to multi-index dataframe.py
"""

import pandas as pd

a = pd.DataFrame([[1, 2]], columns=list('ab'), index=pd.MultiIndex.from_tuples([('A', 1)]))
b = pd.DataFrame([[3, 4]], columns=list('ab'), index=pd.MultiIndex.from_tuples([('B', 2)]))
print(a)
"""
     a  b
A 1  1  2
"""

a = a.append(b)
print(a)
"""
     a  b
A 1  1  2
B 2  3  4
"""

c = pd.Series([5, 6], index=list('ba'))
index = ('C', 3)
a.loc[index, :] = c
print(a)
"""
       a    b
A 1  1.0  2.0
B 2  3.0  4.0
C 3  6.0  5.0
"""

"""
y,  2023.2.12
pandas - groupby axis=1.py
"""

import pandas as pd

a = pd.DataFrame(dict(a=[1, 2], b=[3, 4], c=[5, 6]), index=list('xy'))
a.columns = pd.MultiIndex.from_tuples([('A', 'a'), ('B', 'b'), ('B', 'c')])
print(f"a=\n{a}")
b = a.groupby(axis=1, level=0)
print(f"b.sum()=\n{b.sum()}")

"""
a=
   A  B   
   a  b  c
x  1  3  5
y  2  4  6
b.sum()=
   A   B
x  1   8
y  2  10
"""

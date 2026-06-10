"""
y, pandas - concat different column levels.py, 2019.10.8
"""

import pandas as pd


a = pd.DataFrame([1, 2], columns=['single'])
print(a)

b = pd.DataFrame([3, 4, 5], columns=pd.Index([('1st', '2nd')]))
print(b)

c = pd.concat([a, b], axis=1)
print(c)
print(c.columns)

tuple_columns = [col for col in c.columns if isinstance(col, tuple)]
d = pd.DataFrame(c[tuple_columns], columns=pd.Index(tuple_columns))
print(d)


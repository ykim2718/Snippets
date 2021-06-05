"""
y, 2020.5.12
pandas - groupby last with sort=False.py
"""

import pandas as pd

df = pd.DataFrame({'A': ['foo', 'foo', 'foo', 'bar'],
                   'B': [2, 1, 1, 1],
                   'C': ['a', 'b', 'c', 'd']})
print(df)
last = df.groupby(['A'], sort=True)['C'].last()
print(last)
last = df.groupby(['A'], sort=False)['C'].last()
print(last)

"""
     A  B  C
0  foo  2  a
1  foo  1  b
2  foo  1  c
3  bar  1  d
A
bar    d
foo    c
Name: C, dtype: object
A
foo    c
bar    d
Name: C, dtype: object
"""
"""
y, 2020.11.29
pandas - series - groupby.py
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.Series.groupby.html
"""

import pandas as pd


a = pd.Series([1, 1, 9, 9, 3, 9, 9, 9, 4, 9], index=list('abcdefghij'))
gr = a.groupby(a == 9)
for j, (key, value) in enumerate(gr.groups.items()):
    print(j, f"key={key}, value={value}")

"""
0 key=False, value=Index(['a', 'b', 'e', 'i'], dtype='object')
1 key=True, value=Index(['c', 'd', 'f', 'g', 'h', 'j'], dtype='object')
"""

b = gr.groups[True]
print(b)

"""
Index(['c', 'd', 'f', 'g', 'h', 'j'], dtype='object')
"""

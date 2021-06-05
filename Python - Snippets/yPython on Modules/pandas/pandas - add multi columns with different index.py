"""
y, pandas - add multi columns with different index.py, 2019.1.16
"""

import pandas as pd

a = pd.DataFrame({'A': [1, 2]}, index=list('ab'))
b = pd.DataFrame({'B': [1, 2, 3], 'C': [4, 5, 6]}, index=list('pqr'))
print(a)
print(b)

new_index = a.index.union(b.index)
new_columns = a.columns.union(b.columns)
a = a.reindex(index=new_index, columns=new_columns, fill_value='missing')
print(a)
a.loc[b.index, b.columns] = b.values
print(a)

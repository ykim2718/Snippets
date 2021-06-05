""""
y, pandas - dataframe from dict.py, 2019.11.26
"""

import pandas as pd

a = pd.DataFrame([[1, 2, 3], [4, 5, 6]], columns=list('ABC'), index=list('ab'))
print(a)
b = a.to_dict(orient='index')  # 'dict' is default value.
print(b)
a = pd.DataFrame.from_dict(b, orient='index')  # 'columns' is default value.
print(a)

b = {'a': {'A': 1, 'B': 2, 'C': 3}, 'b': {'A': 4, 'B': 5, 'F': 6}}
a = pd.DataFrame.from_dict(b, orient='index')
print(a)

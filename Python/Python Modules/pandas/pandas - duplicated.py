"""
y, pandas - duplicated.py, 2018.12.15
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.duplicated.html
"""

import pandas as pd

a = pd.DataFrame({'A': [1, 1, 2, 2],
                  'B': [1, 2, 2, 2],
                  'C': [6, 7, 8, 9]})
print(a)
b = a.duplicated(subset=['A', 'B'], keep=False)
print(b)


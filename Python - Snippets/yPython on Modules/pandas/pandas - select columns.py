"""
y, pandas - select columns.py, 2019.1.14
"""

import pandas as pd

a = pd.DataFrame({'A': [1, 2], 'B': [3, 4], 'C': [5, 6]})
print(a[list('AB')])
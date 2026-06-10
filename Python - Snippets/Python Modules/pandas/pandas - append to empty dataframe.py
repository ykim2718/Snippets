"""
y, pandas - append to empty dataframe.py, 2019.2.6
"""

import pandas as pd

a = pd.DataFrame(columns=list('AB'))
b = pd.DataFrame({'B': [1], 'C': [2]})
c = a.append(b, sort=True)
print(c)
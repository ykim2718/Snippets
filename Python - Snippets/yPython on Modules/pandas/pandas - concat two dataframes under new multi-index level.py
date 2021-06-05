"""
y, pandas - concat two dataframes under new multi-index level.py
https://stackoverflow.com/questions/23600582/concatenate-pandas-columns-under-new-multi-index-level
"""

import pandas as pd
import numpy as np

a = pd.DataFrame(np.arange(6).reshape(2, 3), columns=list('ABC'))
b = pd.DataFrame(np.arange(6).reshape(2, 3), columns=list('DEF'))
print(a)
print(b)

c = pd.concat([a, b], axis=1, keys=['first', 'second'])
print(c)

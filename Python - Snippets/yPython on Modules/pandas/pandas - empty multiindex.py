"""
y, 2020.6.10
pandas - empty multiindex.py
"""

import pandas as pd

frame = pd.DataFrame(columns=list('ABC'), index=pd.MultiIndex(levels=[[]]*2, codes=[[]]*2, names=['1st', '2nd']))
print(frame)
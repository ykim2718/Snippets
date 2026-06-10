"""
y, 2021.2.13
pandas - multiindex - create.py
"""

import pandas as pd


index = pd.MultiIndex(levels=[[0], [1]], codes=[[0], [0]], names=('a', 'b'))
print(index)
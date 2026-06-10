"""
y, pandas - datatime.index.py, 2017.10.25
"""

import pandas as pd

index = pd.DatetimeIndex(start='2017-1-1', end='2017-1-31', freq='3D')
print(index)
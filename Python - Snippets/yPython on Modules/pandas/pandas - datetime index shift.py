"""
y, 2018.12.2; 2020.5.3
pandas - datetime index shift.py
"""

import pandas as pd

index = pd.date_range('2018-1-1', '2018-1-11', freq='B')
print(index)
print([idx.strftime("%a") for idx in index])
index = index.shift(2)
print(index)
print([idx.strftime("%a") for idx in index])

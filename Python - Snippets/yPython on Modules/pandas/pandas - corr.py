"""
y, 2024.7.30
pandas - corr.py
"""

import pandas as pd
import numpy as np


f = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [1, 2, 3]
})
print(f"{f.corr()=}")

f = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [2, 1, np.nan]
})
print(f"*{f.corr()=}")
"""
y, 2024.7.30
pandas - corrwith.py
"""

import pandas as pd
import numpy as np


f = pd.DataFrame({'a': [1, 2, 3], 'b': [4, 5, 6]})
g = pd.DataFrame({'a': [1, 2, 3], 'b': [4, 5, 6]})
print(f"{f.corrwith(g, axis=0)=}")

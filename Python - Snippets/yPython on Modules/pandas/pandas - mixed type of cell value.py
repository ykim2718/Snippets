"""
y, 2020.4.27
pandas - mixed type of cell value.py
"""

import pandas as pd

a = pd.DataFrame([None, 1, [2, 3], dict(a=4)])
print(a)
print(a.to_json())

"""
y, pandas - fillna over datetime index.py, 2019.1.25
"""

import pandas as pd

# DO NOT USE THIS # pd.options.mode.use_inf_as_na = True

a = pd.date_range('2019-1-1', '2019-1-5').to_series()
b = a - a.shift(1)
print(b, type(b[0]))
print(b.fillna(0))

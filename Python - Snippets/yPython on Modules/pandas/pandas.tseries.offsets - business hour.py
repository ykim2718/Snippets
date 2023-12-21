"""
y, 2023.12.20 (Wolseley)
pandas.tseries.offsets - business hour.py
https://pandas.pydata.org/docs/reference/api/pandas.tseries.offsets.BusinessHour.html
"""

import pandas as pd


ts = pd.Timestamp(2022, 8, 5, 16)  # Friday
print(f"{ts=}")
print(f"{ts + pd.offsets.BusinessHour(n=0)=}")  # ???
print(f"{ts + pd.offsets.BusinessHour(n=1)=}")  # ???
print(f"{ts + pd.offsets.BusinessHour(n=2)=}")  # ???
print(f"{ts + pd.offsets.BusinessHour(start='09:00')=}")
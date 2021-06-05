"""
y, 2021.5.1
pandas - timestamp.date.py
"""

import pandas as pd

a = pd.Timestamp('2021-5-1 00:00:00', tz='Asia/Seoul')
print(f"a={a}")
print(f"a.date()={a.date()}")
print(f"a.tz_convert('UTC').date()={a.tz_convert('UTC').date()}")
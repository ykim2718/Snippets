"""
y, 2024.7.11
pandas - merge on timestamp.py
"""

import pandas as pd

time_zone = 'Asia/Seoul'
now = pd.Timestamp.now()
now_tz = pd.Timestamp.now(tz=time_zone)

key = 'key'
left = pd.DataFrame({
    key: [now, None, float('nan')],
    'A': ['A0', 'A1', 'A2'],
    'B': ['B0', 'B1', 'B2']
}, dtype=object)
right = pd.DataFrame({
    key: [now_tz, None, float('nan')],
    'C': ['C0', 'C1', 'C2'],
    'D': ['D0', 'D1', 'D2']
})

left[key] = pd.to_datetime(left[key]).dt.tz_localize(time_zone).dt.date
right[key] = pd.to_datetime(right[key]).dt.tz_convert(time_zone).dt.date

print(f"left=\n{left}")
print(f"right=\n{right}")
merged = pd.merge(left, right, on=[key])
print(f"merged=\n{merged}")

"""
y, 2024.7.29
pandas - resample - ohlcv.py
"""

import pandas as pd

f = pd.DataFrame(
    {
        'Open': [5, 6, 7, 8, 9],
        'High': [10, 20, 30, 40, 50],
        'Low': [1, 2, 3, 4, 5],
        'Close': [5, 7, 9, 11, 13],
        'Volume': [1, 2, 3, 4, 5],
    },
    index=pd.to_datetime([
        '2024-01-01', '2024-01-02', '2024-02-05', '2024-03-10', '2024-03-24'
    ]).tz_localize('Asia/Seoul')
)
print(f"{f=}")

aggregation = {
    'Open': 'first',
    'High': 'max',
    'Low': 'min',
    'Close': 'last',
    'Volume': 'sum'
}

g = f.resample('ME').agg(aggregation)
print(g)
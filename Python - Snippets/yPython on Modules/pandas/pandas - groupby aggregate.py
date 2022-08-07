"""
y, 2022.8.6
pandas - groupby aggregate.py
"""

import pandas as pd
import numpy as np

df = pd.DataFrame({'key': list('ABCABC'), 'data1': [1, 2, 3, 1, 2, 3], 'data2': np.random.randint(0, 6, 6)})
print(f"{df=}")

print(f"{df.groupby('key').aggregate(['min', np.median, max])=}")
print(f"{df.groupby('key').aggregate({'data1': 'min', 'data2': np.sum})=}")

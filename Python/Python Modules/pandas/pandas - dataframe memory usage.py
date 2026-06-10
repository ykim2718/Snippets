"""
y, pandas - dataframe memory usage.py, 2018.10.16
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.memory_usage.html
"""

import pandas as pd
import numpy as np
import os

dtypes = ['int64', 'float64', 'complex128', 'object', 'bool']
data = dict([(t, np.ones(shape=5000).astype(t)) for t in dtypes])
df = pd.DataFrame(data)
print(df.head())
print(df.memory_usage(index=True))
print('memory size =', df.memory_usage(index=True).sum())
csv_file = os.path.splitext(__file__)[0] + '.csv'
df.to_csv(csv_file)
print('file size =', os.path.getsize(csv_file))


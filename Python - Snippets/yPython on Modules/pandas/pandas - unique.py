"""
y, pandas - unique.py, 2019.7.20
"""

import pandas as pd
import numpy as np

df = pd.DataFrame({'Col1': ['Bob', 'Joe', 'Bill', 'Mary', 'Joe'],
                   'Col2': ['Joe', 'Steve', 'Bob', 'Bob', 'Steve'],
                   'Col3': np.random.random(5)})
print(df)

print(pd.unique(df[['Col1', 'Col2']].values.ravel('K')))

print(df['Col2'].unique())
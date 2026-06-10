"""
y, Pandas - sparse dataframe.py, 2017.9.14
"""

import pandas as pd
import numpy as np

df = pd.DataFrame(np.random.randn(10000, 4))
df.iloc[:9998] = np.nan
sdf = df.to_sparse()
print(sdf.tail())
print(type(sdf))
print(sdf.density)

df = df.to_dense()
print(df.tail())
print(type(df))

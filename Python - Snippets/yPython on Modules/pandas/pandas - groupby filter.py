"""
y, 2022.8.6
pandas - groupby filter.py
"""

import pandas as pd
import numpy as np

df = pd.DataFrame({'key': list('ABCABC'), 'data1': [1, 2, 3, 1, 2, 3], 'data2': np.random.randint(0, 6, 6)})
print(f"{df=}")


def filter_by_mean(x):
    return x['data2'].mean() > 2


print(f"{df.groupby('key').filter(filter_by_mean)=}")

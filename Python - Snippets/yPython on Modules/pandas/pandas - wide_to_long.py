"""
y, pandas - wide_to_long.py, 2019.1.21
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.wide_to_long.html
"""

import pandas as pd
import numpy as np

np.random.seed(123)
df = pd.DataFrame({
    "A1970": {0: "a", 1: "b", 2: "c"},
    "A1980": {0: "d", 1: "e", 2: "f"},
    "B1970": {0: 2.5, 1: 1.2, 2: .7},
    "B1980": {0: 3.2, 1: 1.3, 2: .1},
    "X": dict(zip(range(3), np.random.randn(3)))
})
df["id"] = df.index
print(df)
df = pd.wide_to_long(df, stubnames=["A", "B"], i="id", j="year")
print(df)

print('-' * 32)

df = pd.concat([
    pd.DataFrame({"A": {0: "a", 1: "b", 2: "c"}, "B": {0: 0, 1: 1, 2: 2}}),
    pd.DataFrame({"A": {0: "d", 1: "e", 2: "f"}, "B": {0: 3, 1: 4, 2: 5}})
], axis=1, keys=['f1', 'f2'])
print(df)
df = df.stack(0)
print(df)

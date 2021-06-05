"""
y, 2020.7.30
dask - select few rows by index.py
"""

import dask.dataframe as dd
import pandas as pd

a = pd.DataFrame(dict(a=[1, 2, 3], b=[4, 5, 6]), index=list('abc'))
print(a)

b = dd.from_pandas(a, npartitions=2)
print(b)

print("b.loc[index[0:2]]".ljust(64, '-'))
# print(b.head(1, npartitions=-1))
index = list(b.index)
# c = b.loc[index[0:2]].compute()  # working
c = b.loc[['a', 'b']].compute()  # working
# c = b.iloc[[0, 1]].compute()  # NotImplementedError: 'DataFrame.iloc' only supports selecting columns. It must be used like 'df.iloc[:, column_indexer]'.
print(c)

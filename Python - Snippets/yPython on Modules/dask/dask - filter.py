"""
y, 2020.7.28 - 29
dask - filter.py
https://docs.dask.org/en/latest/dataframe-api.html#dask.dataframe.from_pandas
"""

import dask.dataframe as dd
import pandas as pd


df = pd.DataFrame(dict(a=list('aabbcc'), b=list(range(6))), index=pd.date_range(start='20100101', periods=6))
print(df)
ddf = dd.from_pandas(df, npartitions=2)
print(ddf.divisions)
# print(ddf.head(npartitions=-1))

print("ddf[ddf.a == 'a']".ljust(64, '-'))
# ddf = ddf[ddf.a == 'a']
ddf = ddf[ddf['a'] == 'a']
print(ddf.head(n=min(len(ddf), 5), npartitions=-1), type(ddf), ddf.shape, len(ddf.index))

print("ddf.compute()".ljust(64, '-'))
df = ddf.compute()
print(df, type(df), df.shape)


"""
y, Pandas - resample time series data.py , 2017.2.11

http://pandas.pydata.org/pandas-docs/stable/timeseries.html
http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.resample.html
"""
import pandas as pd
import numpy as np

rng = pd.date_range('1/1/2011', periods=10, freq='B')
print(rng)
ds = pd.Series(np.random.randn(len(rng)), index=rng)
print(ds)
ds = ds.resample('W').mean()
print(ds)

df = pd.DataFrame({'a': np.random.randn(len(rng)), 'b': np.random.randn(len(rng)),}, index=rng)
print(df)
print(df.resample('W').mean())
print(df.resample('W').median())
print(df.resample('W').first())
print(df.resample('W').last())
print(df.resample('W').std())
print(df.resample('W').count())
print(df.resample('W').min())
print(df.resample('W').max())
print(df.resample('W').sum())
print(df.resample('3d').sum())



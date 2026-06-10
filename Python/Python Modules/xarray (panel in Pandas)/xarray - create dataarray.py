"""
y, xarray - create dataarray.py, 2018.7.22 - 23 (Monpetit)
http://xarray.pydata.org/en/stable/examples/quick-overview.html#create-a-dataarray
"""

import xarray as xr
import numpy as np
import pandas as pd

da = xr.DataArray(np.random.randn(2, 3))
print(da)

da = xr.DataArray(np.random.randn(2, 3, 4))
print(da)

da = xr.DataArray(np.random.randn(2, 3), coords={'x': ['a', 'b']}, dims=('x', 'y'))
print(da)

da = xr.DataArray(np.random.randn(2, 3, 4), coords={'x': ['a', 'b']}, dims=('x', 'y', 'z'))
print(da)

df = pd.DataFrame({'A': [1, 1, 2],
                   'B': ['foo', 'bar', 'foo'],
                   'C': np.arange(4., 7)}
                  ).set_index(['B', 'A'])
da = xr.DataArray(df)
print(da)
print(da.to_pandas())

dfs = []
dfs.append(xr.DataArray(df))
dfs.append(xr.DataArray(df))
dfs.append(xr.DataArray(df))
da = xr.concat(dfs, dim=['first', 'second', 'third'])
print(da)
"""
<xarray.DataArray (dim_0: 3, dim_1: 1)>
array([[4.],
       [5.],
       [6.]])
Coordinates:
  * dim_0    (dim_0) MultiIndex
  - B        (dim_0) object 'foo' 'bar' 'foo'
  - A        (dim_0) int64 1 1 2
  * dim_1    (dim_1) object 'C'
dim_1    C
B   A     
foo 1  4.0
bar 1  5.0
foo 2  6.0
"""
print(da.to_pandas())
"""
<xarray.DataArray (concat_dim: 3, dim_0: 3, dim_1: 1)>
array([[[4.],
        [5.],
        [6.]],

       [[4.],
        [5.],
        [6.]],

       [[4.],
        [5.],
        [6.]]])
Coordinates:
  * dim_0       (dim_0) MultiIndex
  - B           (dim_0) object 'foo' 'bar' 'foo'
  - A           (dim_0) int64 1 1 2
  * dim_1       (dim_1) object 'C'
  * concat_dim  (concat_dim) <U6 'first' 'second' 'third'
"""
print(type(da.to_pandas()))
"""
<class 'pandas.core.panel.Panel'>
Dimensions: 3 (items) x 3 (major_axis) x 1 (minor_axis)
Items axis: first to third
Major_axis axis: (foo, 1) to (foo, 2)
Minor_axis axis: C to C
<class 'pandas.core.panel.Panel'>`
"""



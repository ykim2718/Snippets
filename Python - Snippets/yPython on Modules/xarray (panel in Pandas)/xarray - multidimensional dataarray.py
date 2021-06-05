"""
y, xarray - multidimensional dataarray.py, 2018.7.23
https://rabernat.github.io/research_computing/xarray.html
"""

import numpy as np
import xarray as xr

argo_data = np.load('argo_float_4901412.npz')
print(argo_data.keys())

S = argo_data.f.S
T = argo_data.f.T
P = argo_data.f.P
levels = argo_data.f.levels
lon = argo_data.f.lon
lat = argo_data.f.lat
date = argo_data.f.date
print(S.shape, lon.shape, date.shape)

da_salinity = xr.DataArray(S, dims=['level', 'date'], coords={'level': levels, 'date': date},)
print(da_salinity)

import matplotlib.pyplot as plt
da_salinity.plot(yincrease=False)
plt.show()

da_salinity.attrs['units'] = 'PSU'
da_salinity.attrs['standard_name'] = 'sea_water_salinity'
print(da_salinity)

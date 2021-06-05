"""
y, xarray - dataarray.py, 2018.7.23
https://rabernat.github.io/research_computing/xarray.html
"""

import numpy as np
import xarray as xr
from matplotlib import pyplot as plt

plt.rcParams['figure.figsize'] = (8,5)

da = xr.DataArray([9, 0, 2, 1, 0],
                  dims=['x'],
                  coords={'x': [10, 20, 30, 40, 50]})
print(da)

da.plot(marker='o')
plt.show()


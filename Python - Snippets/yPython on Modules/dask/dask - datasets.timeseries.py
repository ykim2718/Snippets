"""
y, 2020.2.10, 7.30
dask - datasets.timeseries.py
https://examples.dask.org/dataframes/01-data-access.html
"""


import dask
print(f"dask.__version__={dask.__version__}")  # 2.10.1

df = dask.datasets.timeseries(seed=777)  # random
print(df.shape)
print(df.head())
print(df.x)
print(df.y)

'''
import matplotlib.pyplot as plt

fig = plt.figure()
ax1 = fig.add_subplot()
ax1.plot(df.x, df.y)
plt.show()
'''

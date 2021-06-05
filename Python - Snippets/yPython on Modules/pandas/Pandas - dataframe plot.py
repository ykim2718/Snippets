"""
y, 2016.8.22, Pandas - dataframe plot.py
"""
import pandas as pd
import matplotlib.pyplot as plt


def get_sample_dataframe():
    from numpy import arange, sin, pi
    t = arange(0.0, 3.0, 0.01)
    s = sin(2 * pi * t)
    df = pd.DataFrame({'x': t, 'y': s})
    return df


df = get_sample_dataframe()
fig, ax = plt.subplots(nrows=1, ncols=1)
df.plot(x='x', y='y', ax=ax, kind='line')
plt.show()

"""
y, pandas - plot with colormap.py, 2017.10.25
"""

import pandas as pd
import numpy as np


def get_colormap(y, colors=['r', 'g', 'b']):
    """
    +y, 2017.10.25 - 26

    Usage
    -----
    colormap = get_colormap(pd.Series(y))
    pd.DataFrame(X).plot(kind='scatter', x=0, y=1, c=get_colormap(pd.Series(y))

    """

    labels = np.unique(y)
    if len(labels) > len(colors):
        colors = np.tile(colors, len(labels) // len(colors) + 1)
    colormap = dict(zip(labels, colors))
    print(colormap)
    if hasattr(y, 'replace'):
        return y.replace(colormap)
    else:
        return pd.Series(y).replace(colormap)


df = pd.DataFrame(np.random.randint(0, 99, size=(5, 2)), columns=list('AB'))
# print(df)

colormap = get_colormap(df['B'])
df.plot(kind='scatter', style=['ro--', 'bo--'], x='A', y='B', c=colormap, s=99)

import matplotlib.pyplot as plt
plt.title(__file__)
plt.show()

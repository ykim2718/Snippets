"""
y, pandas - plot.py, 2017.10.24; 2020.10.27
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.plot.html
https://matplotlib.org/3.1.1/api/markers_api.html
"""

import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import matplotlib as mpl
import pathlib

frame = pd.DataFrame(np.random.randint(0, 99, size=(5, 2)), columns=['one', 'two'])
print(frame)

fig = plt.figure()
fig.canvas.manager.set_window_title(pathlib.Path(__file__).name)
title = 'pd.DataFrame.plot()'
fig.suptitle(title)
gs = mpl.gridspec.GridSpec(2, 1)
ax1 = fig.add_subplot(gs[0, 0])
# ax2 = fig.add_subplot(gs[1, 0], sharex=ax1)
# fig.align_ylabels([ax1, ax2])
# fig.subplots_adjust(wspace=0, hspace=0)

# frame.plot(x='one', y='two', style='o--', title='dataframe plot')
frame.plot(ax=ax1, style=['o--', 'rx-'], markersize=5, title='sample plot')
ax1.set(xlabel='x axis label', ylabel='y label', ylim=(0, 110))

plt.show()

"""
y, mpl - multiple bar chart.py, 2019.4.8
https://matplotlib.org/api/_as_gen/matplotlib.axes.Axes.bar.html
https://matplotlib.org/gallery/units/bar_unit_demo.html
"""

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

frame = pd.DataFrame({'A': [1, 2, 3], 'B': [4, 5, 6]}, index=list('abc'))
x_locs = np.arange(len(frame))
bar_width = 0.3

fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(5, 5))
ax1.bar(x_locs, frame.A, width=bar_width, color='r', label='A')
ax1.bar(x_locs + bar_width, frame.B, width=bar_width, color='b', label='B')
ax1.set_xticks(x_locs + bar_width / 2)
ax1.set_xticklabels(frame.index)
ax1.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left')

plt.show()
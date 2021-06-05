"""
y, 2021.3.22
mpl - gridspec loop.py
"""

import matplotlib.pyplot as plt
import matplotlib as mpl
import pathlib
import pandas as pd

fig = plt.figure()
fig.set_size_inches(9, 6)
fig.set_dpi(100)
fig.subplots_adjust(hspace=0, wspace=0)
title = f"{pathlib.Path(__file__).stem}"
window_title = f"{title}.py ... {pd.Timestamp.now()}"
fig.canvas.set_window_title(window_title)
title += '\nGridSpec(4,6)'
fig.suptitle(title, fontsize='medium')
gs = mpl.gridspec.GridSpec(4, 6)
axes = []
for j in range(gs.nrows):
    for k in range(gs.ncols):
        if j == k == 0:
            ax = fig.add_subplot(gs[j, k])
        else:
            ax = fig.add_subplot(gs[j, k], sharex=axes[0], sharey=axes[0])
        axes.append(ax)
        i = axes.index(ax)
        ax.plot([1], [1], marker='.', ms=2, c='r', linestyle='-', linewidth=1, alpha=0.3)
        ax.set_title(f"i={i}", x=0.02, y=0, loc='left', ha='left', fontsize='x-small')
        if j == gs.nrows - 1 and k == 0:
            ax.xaxis.set_tick_params(labelsize='x-small')
            ax.yaxis.set_tick_params(labelsize='x-small')
            ax.set_ylabel('y label', fontsize='x-small')
            ax.set_xlabel('x label', fontsize='x-small')
        else:
            ax.xaxis.set_visible(False)
            ax.yaxis.set_visible(False)
plt.show()
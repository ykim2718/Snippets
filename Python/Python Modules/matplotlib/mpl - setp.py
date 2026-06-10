"""
y, 2021.3.4
mpl - setp.py
"""

import matplotlib as mpl
import matplotlib.pyplot as plt
import pathlib

fig = plt.figure()
title = pathlib.Path(__file__).stem
fig.canvas.manager.set_window_title(title)
fig.suptitle(title)
ax1 = fig.add_subplot()
plt.setp(ax1, xscale='linear', yscale='log', xlabel='last_price', ylabel='target_price', title='adj_price')
print(mpl.artist.kwdoc(ax1))
plt.show()

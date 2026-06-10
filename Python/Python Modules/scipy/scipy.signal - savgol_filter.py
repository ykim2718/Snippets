"""
y, scipy.signal - savgol_filter.py.py, 2018.11.25
https://stackoverflow.com/questions/37598986/reducing-noise-on-data
"""

import os
import numpy as np
import matplotlib.pyplot as plt

fig, (ax1, ax2) = plt.subplots(nrows=2, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

title = os.path.basename(__file__)
fig.suptitle(title, fontsize='large')
fig.canvas.manager.set_window_title(title)

mu, sigma = 0, 500

x = np.arange(1, 100, 0.1)  # x axis
z = np.random.normal(mu, sigma, len(x))  # noise
y = x ** 2 + z  # data
ax1.plot(x, y, linewidth=2, linestyle="-", c="b")  # it include some noise


# After filter

from scipy.signal import savgol_filter
window_length = 101
w = savgol_filter(y, window_length, 2)
ax2.plot(x, w, 'b')  # high frequency noise removed

plt.show()
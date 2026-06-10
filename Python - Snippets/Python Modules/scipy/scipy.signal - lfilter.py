"""
y, scipy.signal - lfilter.py, 2018.11.25
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

from scipy.signal import lfilter

n = 15  # the larger n is, the smoother curve will be
b = [1.0 / n] * n
a = 1
yy = lfilter(b, a, y)
ax2.plot(x, yy, linewidth=2, linestyle="-", c="b")  # smooth by filter

plt.show()
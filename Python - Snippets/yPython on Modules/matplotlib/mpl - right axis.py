"""
y, 2021.12.27 (Somerled)
mpl - right axis.py

https://pythonguides.com/matplotlib-tick-params/
https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.tick_params.html
"""

import matplotlib.pyplot as plt
import numpy as np

x = np.arange(100)
y = np.sin(x)

plt.plot(x, y)

plt.tick_params(left=False, right=True, top=True, labelleft=False, labelright=True, labeltop=True)

plt.show()
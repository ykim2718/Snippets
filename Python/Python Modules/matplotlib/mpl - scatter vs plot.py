"""
y, mpl - scatter vs plot.py, 2018.3.9
"""

import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax1 = fig.add_subplot(1, 2, 1)
ax2 = fig.add_subplot(1, 2, 2)
x = np.array([0, 1, 2, 3])
ax1.scatter(x, x, marker='o', c='r', s=50, linewidths=1, label='scatter')
ax1.set_title('ax1.scatter()')
ax2.plot(x, x, marker='o', c='r', ms=10, lw=0, label='plot')
ax2.set_title('ax1.plot()')
plt.show()

"""
y, 2016.9.9; 2021.12.27 (Somerled)
mpl - multicursor.py
http://matplotlib.org/1.5.1/examples/widgets/multicursor.html
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import MultiCursor

t = np.arange(0.0, 2.0, 0.01)
s1 = np.sin(2*np.pi*t)
s2 = np.sin(4*np.pi*t)
fig = plt.figure()
ax1 = fig.add_subplot(211)
ax1.plot(t, s1)


ax2 = fig.add_subplot(212, sharex=ax1)
ax2.plot(t, s2)

multi = MultiCursor(fig.canvas, (ax1, ax2), color='r', lw=1, vertOn=False, horizOn=True)
plt.show()
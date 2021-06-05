"""
y, 2016.9.4, add_axes_sharing_x.py
http://matplotlib.org/users/artists.html
http://matplotlib.org/examples/pylab_examples/shared_axis_demo.html
"""
import matplotlib.pyplot as plt
import numpy as np

figure = plt.figure()
ax1 = figure.add_axes([0.15, 0.5, 0.7, 0.4])  # [left, bottom, width, height]
t = np.arange(0.0, 1.0, 0.01)
s = np.sin(2*np.pi*t)
line, = ax1.plot(t, s, color='blue', lw=2)

ax2 = figure.add_axes([0.15, 0.1, 0.7, 0.3], sharex=ax1)
ax2.plot(t, s, color='blue', lw=2)

plt.show()


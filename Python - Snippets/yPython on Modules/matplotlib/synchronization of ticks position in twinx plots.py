"""
http://matplotlib.1069221.n5.nabble.com/synchronization-of-ticks-position-in-twinx-plots-td39097.html
y, 2016.4.28
"""
import matplotlib.pyplot as plt

ax1 = plt.subplot(111)
ax1.plot([1, 2, 3], 'bo-')
ax1.grid(True)

ax2 = plt.twinx(ax1)
ax2.plot([11, 12], 'rs-')
ax2.grid(True)

ax1.set_xlim(-0.5, 2.5)

plt.show()

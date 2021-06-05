"""
y, 2016.9.4
http://matplotlib.org/users/gridspec.html
"""
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

gs = gridspec.GridSpec(2, 2, width_ratios=[1, 2], height_ratios=[4, 1])
ax1 = plt.subplot(gs[0])
ax2 = plt.subplot(gs[1])
ax3 = plt.subplot(gs[2])
ax4 = plt.subplot(gs[3])

plt.show()

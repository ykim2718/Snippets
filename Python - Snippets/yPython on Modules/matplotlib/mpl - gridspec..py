"""
y, 2016.9.4; 2020.2.8; 2021.6.21
mpl - gridspec.py
http://matplotlib.org/users/gridspec.html
https://matplotlib.org/gallery/subplots_axes_and_figures/align_labels_demo.html#sphx-glr-gallery-subplots-axes-and-figures-align-labels-demo-py
"""

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

fig = plt.figure()
gs = gridspec.GridSpec(2, 4, width_ratios=[1, 2, 3, 4], height_ratios=[4, 1])

ax1 = fig.add_subplot(gs[0, :])
ax2 = fig.add_subplot(gs[1, 0])
ax3 = fig.add_subplot(gs[1, 1])
ax4 = fig.add_subplot(gs[1, 3])

plt.show()
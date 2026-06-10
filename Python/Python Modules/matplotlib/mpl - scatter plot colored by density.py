"""
y, mpl - scatter plot colored by density.py, 2018.1.3

How can I make a scatter plot colored by density in matplotlib?
https://stackoverflow.com/questions/20105364/how-can-i-make-a-scatter-plot-colored-by-density-in-matplotlib

pylab_examples example code: show_colormaps.py
https://matplotlib.org/1.2.1/examples/pylab_examples/show_colormaps.html

"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import gaussian_kde

# Generate fake data
x = np.random.normal(size=1000)
y = x * 3 + np.random.normal(size=1000)

# Calculate the point density
xy = np.vstack([x,y])
z = gaussian_kde(xy)(xy)

# Sort the points by density, so that the densest points are plotted last
idx = z.argsort()
x, y, z = x[idx], y[idx], z[idx]

fig, ax = plt.subplots()
cmap = plt.cm.RdYlBu
cmap = plt.cm.autumn
cmap = plt.cm.winter
cmap = plt.cm.jet  # good-looking
ax.scatter(x, y, c=z, s=50, edgecolor='', cmap=cmap)
plt.show()
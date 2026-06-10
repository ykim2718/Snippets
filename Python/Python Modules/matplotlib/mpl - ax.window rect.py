"""
y, mpl - ax.window rect.py, 2019.4.8
"""

import matplotlib.pyplot as plt

fig, ax1 = plt.subplots(nrows=1, ncols=1, figsize=(5, 5))
ax2 = fig.add_axes([0.5, 0.5, 0.1, 0.1])

for name, ax in zip(['ax1', 'ax2'], [ax1, ax2]):
    bbox = ax.get_position()
    print(name, bbox, type(bbox), "x0={x0}, y0={y0}, w={w}, h={h}".format(
        x0=bbox.x0, y0=bbox.y0, w=bbox.width, h=bbox.height))

plt.show()

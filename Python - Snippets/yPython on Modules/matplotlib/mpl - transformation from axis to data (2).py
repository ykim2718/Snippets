"""
y, 2023.1.18
mpl - transformation from axis to data (2).py
https://stackoverflow.com/questions/62004022/convert-from-data-coordinates-to-axes-coordinates-in-matpltlib
"""

import matplotlib.pyplot as plt

fig, ax = plt.subplots()
point = (100, 100)  # this is in data coordinates
trans = ax.transData.transform(point)
trans = ax.transAxes.inverted().transform(trans)
print(ax.get_xlim(), trans)
# (0.0, 1.0) [100. 100.]

ax.set_xlim(0, 200)
ax.set_ylim(0, 200)
trans = ax.transData.transform(point)
trans = ax.transAxes.inverted().transform(trans)
print(ax.get_xlim(), trans)
# (0.0, 200.0) [0.5 0.5]

"""
y, mpl - many figures.py, 2019.7.10
"""

import matplotlib.pyplot as plt

fig, ax1 = plt.subplots(1, 1, figsize=[3, 3])
ax1.plot([3, 1, 4, 1, 5], 'ks-', mec='w', mew=2, ms=10)

fig, ax1 = plt.subplots(1, 1, figsize=[3, 3])
ax1.plot([3, 1, 4, 1, 5], 'ks-', mec='w', mew=2, ms=10)

plt.show()

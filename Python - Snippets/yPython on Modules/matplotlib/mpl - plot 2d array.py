"""
y, mpl - plot 2d array.py, 2018.11.14
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

fig = plt.figure()

X = [[1, 1, 1, 1], [2, 2, 2, 2], [3,  3,  3,  3], [ 4,  4,  4,  4]]
Y = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
ax1 = fig.add_subplot(221)
ax1.plot(X, Y, 'ro-')

X = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
Y = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
ax2 = fig.add_subplot(222)
ax2.plot(X, Y, 'go-')

X = [[1, 2, 3, 4], [1, 2, 3, 4], [1,  2,  3,  4], [ 1,  2,  3,  4]]
Y = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
ax3 = fig.add_subplot(223)
ax3.plot(X, Y, 'bo-')

X = np.array(X).T.tolist()
print(X)
Y = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
ax4 = fig.add_subplot(224)
ax4.plot(X, Y, 'bo-')

plt.show()
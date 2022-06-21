"""
y, 2022.6.21
mpl - real time scatter.py
https://www.delftstack.com/ko/howto/matplotlib/how-to-plot-in-real-time-using-matplotlib/
https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.ion.html
"""

import numpy as np
import matplotlib.pyplot as plt

x = 0
for i in range(100):
    x = x + 0.04
    y = np.sin(x)
    plt.scatter(x, y)
    plt.title("Real Time plot")
    plt.xlabel("x")
    plt.ylabel("sinx")
    plt.pause(0.05)

plt.show()

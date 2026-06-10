"""
y, 2022.6.21
mpl - real time plot.py
https://www.delftstack.com/ko/howto/matplotlib/how-to-plot-in-real-time-using-matplotlib/
https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.ion.html
"""

import numpy as np
import time
import matplotlib.pyplot as plt

x = np.linspace(0, 10, 100)
y = np.cos(x)

plt.ion()

figure, ax = plt.subplots(figsize=(8, 6))
line1, = ax.plot(x, y)

plt.title("Dynamic Plot of sinx", fontsize=25)

plt.xlabel("X", fontsize=18)
plt.ylabel("sinX", fontsize=18)

for p in range(100):
    updated_y = np.cos(x - 0.05 * p)

    line1.set_xdata(x)
    line1.set_ydata(updated_y)

    figure.canvas.draw()

    figure.canvas.flush_events()
    time.sleep(0.1)

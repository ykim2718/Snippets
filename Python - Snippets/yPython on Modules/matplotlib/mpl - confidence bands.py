"""
y, 2020.6.25
mpl - confidence bands.py
https://matplotlib.org/gallery/lines_bars_and_markers/fill_between_demo.html#example-confidence-bands
"""

import matplotlib.pyplot as plt
import numpy as np

N = 21
x = np.linspace(0, 10, 11)
y = [3.9, 4.4, 10.8, 10.3, 11.2, 13.1, 14.1,  9.9, 13.9, 15.1, 12.5]

# fit a linear curve an estimate its y-values and their error.
a, b = np.polyfit(x, y, deg=1)
y_est = a * x + b
y_err = x.std() * np.sqrt(1/len(x) + (x - x.mean())**2 / np.sum((x - x.mean())**2))  # ★★★

fig, ax = plt.subplots()
ax.plot(x, y_est, '-')
ax.fill_between(x, y_est - y_err, y_est + y_err, alpha=0.2)
ax.plot(x, y, 'o', color='tab:brown')

ax.set_title('Confidence Bands', y=0.95, va='top')

plt.show()
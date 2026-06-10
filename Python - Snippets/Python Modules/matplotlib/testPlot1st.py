"""
y, 2016.4.25
matplotlib.org/api/pyplot_api.html#matplotlib.pyplot.annotate3
matplotlib annotate arrow example 찾을 것
matplotlib.org/examples/pylab_examples/subplots_demo.html
"""

import matplotlib.pyplot as plt
import numpy as np

# Simple data to display in various forms
x = np.linspace(0, 2 * np.pi, 400)
y = np.sin(x ** 2)

# plt.close('all')

# Just a figure and one subplot
f, ax = plt.subplots()
ax.plot(x, x)
ax.plot(x, y)
ax.set_title('Simple plot')

# ax.set_aspect('equal')  # ??
ax.annotate('#',
            xy=(2, 0), xycoords='data',
            xytext=(20, 20), textcoords='offset points',
            arrowprops=dict(arrowstyle='->', color='r'))

plt.show()

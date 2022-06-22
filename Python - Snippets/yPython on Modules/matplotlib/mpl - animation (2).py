"""
y, 2022.6.22
mpl - animation (2).py
https://stackoverflow.com/questions/17212722/matplotlib-imshow-how-to-animate
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

fig = plt.figure()

fps = 2  # frame per second
n_seconds = 5

snapshots = [np.random.rand(5, 5) for _ in range(n_seconds * fps)]
a = snapshots[0]
im = plt.imshow(a, interpolation='none', aspect='auto', vmin=0, vmax=1)


def animate_func(i, im=im):
    im.set_array(snapshots[i])
    return [im]


anim = FuncAnimation(fig, animate_func, frames=n_seconds * fps, interval=1000 / fps, repeat=True)
plt.show()

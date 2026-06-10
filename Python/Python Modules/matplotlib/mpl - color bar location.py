"""
y, 2021.3.18
mpl - color bar location.py
[1] https://www.geeksforgeeks.org/how-to-adjust-the-position-of-a-matplotlib-colorbar/
[2] https://matplotlib.org/stable/gallery/subplots_axes_and_figures/colorbar_placement.html
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable

# make this example reproducible
np.random.seed(1)

if False:  # [1]
    # create chart
    fig, ax = plt.subplots()
    im = ax.imshow(np.random.rand(15, 15))
    ax.set_xlabel('x-axis label')
    ax.set_title('Colorbar above chart')
    # add color bar below chart
    divider = make_axes_locatable(ax)
    cax = divider.new_vertical(size='5%', pad=0.5)
    fig.add_axes(cax)
    fig.colorbar(im, cax=cax, orientation='horizontal')
else:  # [2]
    fig, axs = plt.subplots(3, 3, constrained_layout=True)
    for ax in axs.flat:
        pcm = ax.pcolormesh(np.random.random((20, 20)))
    fig.colorbar(pcm, ax=axs[0, :2], shrink=0.6, location='bottom')
    fig.colorbar(pcm, ax=[axs[0, 2]], location='bottom')
    fig.colorbar(pcm, ax=axs[1:, :], location='right', shrink=0.6)
    fig.colorbar(pcm, ax=[axs[2, 1]], location='left')

plt.show()
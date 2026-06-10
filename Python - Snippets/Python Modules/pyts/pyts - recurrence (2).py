"""
y, 2020.1.14 - 15
pyts - recurrence (2).py
https://en.wikipedia.org/wiki/Recurrence_plot
https://laszukdawid.com/tag/recurrence-plot/
https://pyts.readthedocs.io/en/latest/auto_examples/image/plot_rp.html
https://pyts.readthedocs.io/en/latest/generated/pyts.image.RecurrencePlot.html#pyts.image.RecurrencePlot
https://en.wikipedia.org/wiki/Phase_space
"""

from pyts.image import RecurrencePlot

if True:
    import pandas as pd
    import numpy as np

    file_path = './A000020-day.csv'
    frame = pd.read_csv(file_path)
    print(f"frame.shape={frame.shape}")
    X = frame['close'].values
    X = np.expand_dims(X[-100:], axis=0)  # np.expand_dims(x, axis=0) is equivalent to x[np.newaxis,:] or x[np.newaxis]
    print(f"X.shape={X.shape}")  # (1, 100)
else:
    from pyts.datasets import load_gunpoint

    X, _, y, _ = load_gunpoint(return_X_y=True)
    X = X[:1, :]
    print(f"X.shape={X.shape}")  # (50, 150)
    print(f"y.shape={y.shape}")  # (50,)

# Recurrence plot transformation
rp = RecurrencePlot(threshold='point', percentage=20)
X_rp = rp.fit_transform(X)
print(f"X_rp.shape={X_rp.shape}, (min, max)=({X_rp.min()}, {X_rp.max()})")

import pathlib

file_name = pathlib.Path(__file__).name

import matplotlib.pyplot as plt
import matplotlib.gridspec as mpl_gs

fig = plt.figure(constrained_layout=True)
gs = mpl_gs.GridSpec(1, 2, figure=fig)
ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[0, 1])

title = file_name
fig.canvas.manager.set_window_title(title)
plt.suptitle(title)
ax1.imshow(X_rp[0], cmap='binary', origin='lower')
ax1.set_title('Recurrence Plot')
ax2.plot(range(X.shape[1]), X[0], marker='.', ms=4, c='k', ls='-', lw=3, alpha=0.2)
ax2.set_title('Pebble Trend')
plt.show()

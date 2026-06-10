"""
y, 2021.1.27
pywt - pebble.py
https://youtu.be/Qryd7z9k8i4  >> Wavelet Transform Analysis of 1-D signals using Python
https://community.backtrader.com/topic/1312/haar-wavelet-with-lifting-and-incremental-option  ★
https://pywavelets.readthedocs.io/en/latest/ref/signal-extension-modes.html#ref-modes
"""

import pandas as pd
import numpy as np
import pathlib
import pywt
import matplotlib.pyplot as plt
import matplotlib as mpl

folder_path = pathlib.Path(__file__).parent.parent.parent / 'yPython on Machine Learning' / 'data'
csv_path = folder_path / 'A000030-day.csv'
x = pd.read_csv(str(csv_path), index_col=0, parse_dates=True, usecols=['date', 'aclose'])['aclose']
x = x[:365]
x = np.log10(x)

cA, cD = pywt.dwt(x, 'haar', mode='per')  # wavelet transform
y = pywt.idwt(cA, cD, 'haar', mode='per')  # inverse wavelet transform

print(f"x={len(x)}")  # signal
print(f"cA={len(cA)}")  # approximation coeffs
print(f"cD={len(cD)}")  # detailed coeffs

print(x.index[0], x.index[-1])
cA = pd.Series(cA, index=x.index[::2])
cD = pd.Series(cD, index=cA.index)

x = x/x.max()
cA = cA/cA.max()

fig = plt.figure(figsize=(9, 6))
fig.canvas.manager.set_window_title(pathlib.Path(__file__).name)
fig.subplots_adjust(hspace=0)
gs = mpl.gridspec.GridSpec(2, 1)
ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[1, 0], sharex=ax1)
ax1.plot(x, marker='.', ms=3, ls='-', lw=1, c='C0', alpha=0.7, label='signal')
ax1.plot(cA, marker='.', ms=3, ls='-', lw=1, c='C1', alpha=0.7, label='cA')
ax2.plot(cD, marker='.', ms=3, ls='-', lw=1, c='C2', alpha=0.7, label='cD')
for ax in fig.axes:
    ax.legend(loc='upper left', fontsize='small')
plt.show()


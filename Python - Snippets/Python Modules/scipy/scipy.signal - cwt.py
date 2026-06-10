"""
y, scipy.signal - cwt.py, 2019.8.21 - 22, 9.15, 9.23, 11.11, 11.14
https://docs.scipy.org/doc/scipy-0.15.1/reference/generated/scipy.signal.cwt.html
https://docs.scipy.org/doc/scipy-0.15.1/reference/generated/scipy.signal.ricker.html
https://en.wikipedia.org/wiki/Continuous_wavelet_transform

Note
----
CWT = Continuous Wavelet Transform
CWT can convert time series data to image data
"""


import numpy as np
from scipy import signal
import matplotlib.pyplot as plt

t = np.linspace(-1, 1, 200, endpoint=False)
sig = np.cos(2 * np.pi * 7 * t) + signal.gausspulse(t - 0.4, fc=2)
widths = np.arange(1, 31)
# sig = sig[-100:]
cwtmatr = signal.cwt(sig, signal.ricker, widths)
print('sig=', sig.shape)  # (200,)
print('cwtmatr=', cwtmatr.shape)  # (30, 200)

import pathlib

title = pathlib.Path(__file__).name
plt.suptitle(title)
plt.subplot(2, 1, 1)
plt.plot(sig)
plt.subplot(2, 1, 2)
if False:
    plt.imshow(cwtmatr, extent=[-1, 1, 1, 31], cmap='PRGn', aspect='auto',
               vmax=abs(cwtmatr).max(), vmin=-abs(cwtmatr).max())
else:
    plt.imshow(cwtmatr, cmap='PRGn', aspect='auto') #  vmax=abs(cwtmatr).max(), vmin=-abs(cwtmatr).max())

# 2019.11.11, 11.14
print('cwtmatr[:, -1]=', cwtmatr[:, -1])
sig_ = sig[-50:]
widths = np.arange(1, 11)
cwtmatr = signal.cwt(sig_, signal.ricker, widths)
print('sig=', sig_.shape)  # (50,)
print('cwtmatr[:, -1]=', cwtmatr[:, -1], 'shape=', cwtmatr.shape)  # (10, 50)
widths = np.arange(1, 6)
cwtmatr = signal.cwt(sig_, signal.ricker, widths)
print('cwtmatr[:, -1]=', cwtmatr[:, -1], 'shape=', cwtmatr.shape)  # (5, 50)
sig_ = sig[-10:]; cwtmatr = signal.cwt(sig_, signal.ricker, widths)
print('cwtmatr[:, -1]=', cwtmatr[:, -1], 'shape=', cwtmatr.shape)  # (5, 10)
sig_ = sig[:50]; cwtmatr = signal.cwt(sig_, signal.ricker, widths)
print('cwtmatr[:, 0]=', cwtmatr[:, 0], 'shape=', cwtmatr.shape)  # (5, 50)
sig_ = sig[:10]; cwtmatr = signal.cwt(sig_, signal.ricker, widths)
print('cwtmatr[:, 0]=', cwtmatr[:, 0], 'shape=', cwtmatr.shape)  # (5, 10)

plt.show()


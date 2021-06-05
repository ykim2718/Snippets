"""
y, numpy - fft.py, 2018.11.27
https://docs.scipy.org/doc/numpy-1.15.1/reference/generated/numpy.fft.fft.html
https://pinkwink.kr/708
https://pinkwink.kr/707?category=522424
https://stackoverflow.com/questions/25735153/plotting-a-fast-fourier-transform-in-python
"""

import numpy as np

wave_frequency = 0.5  # period=1/frequency
time_span = 10
time_step = 0.1
n_sigma_cut = 2

n = int(time_span/time_step)
x = np.arange(n)*time_step
y = np.sin(2*np.pi*wave_frequency*x)
sp = np.fft.fft(y)  # y, spectrum

# single-sided amplitude spectrum
spectrum = abs(sp/n)[:n//2]  # n, just for looking-good scaling
frequency = np.fft.fftfreq(n, d=time_step)[:n//2]
if n_sigma_cut is not None:
    m, s = np.mean(spectrum), np.std(spectrum)
    cut = m + s * n_sigma_cut
    mask = spectrum > cut
    spectrum = spectrum[mask]
    frequency = frequency[mask]


import matplotlib.pyplot as plt
import os
fig, ax = plt.subplots(2, 1)
title = os.path.basename(__file__)
fig.suptitle(title, fontsize='large')
fig.canvas.set_window_title(title)

ax[0].plot(x, y)
ax[0].set_xlabel('time')
ax[0].set_ylabel('amplitude')
if False:
    ax[1].plot(frequency, spectrum)
else:
    color = 'r'
    for f, s in zip(frequency, spectrum):
        ax[1].plot([f, f], [0, s], color, linestyle='-')
        ax[1].plot(f, s, color, marker='^')
ax[1].set_xlabel('frequency, f')
ax[1].set_ylabel('|Y(f)|')
plt.show()


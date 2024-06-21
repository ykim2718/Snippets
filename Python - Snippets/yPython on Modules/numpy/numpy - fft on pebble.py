"""
y, numpy - fft on pebble.py, 2018.11.27
"""

import pandas as pd
import numpy as np

start_time, stop_time = '2017-11-1', '2017-12-31'
start_time, stop_time = '2017-10-15', '2017-12-15'
# start_time, stop_time = '2017-10-1', '2017-11-30'
csv_file_path = r'..\_data\a000030-day.csv'
n_sigma_cut = 0
trend = 'seasonal_decomposed_trend'
polyorder_of_filter = 4
seaonsal_decomposition_freq = 5

frame = pd.read_csv(csv_file_path, index_col=0, parse_dates=True, dtype=np.float32)
y = frame.loc[start_time:stop_time, 'close'].values
n = len(y)
x = range(n)

# extract trend
if trend == 'savgol_trend':
    from scipy.signal import savgol_filter
    window_length = n//2
    if window_length % 2 == 0:  # make odd if even
        window_length += 1
    y2 = savgol_filter(y, window_length, polyorder_of_filter)
    y3 = y - y2
elif trend == 'seasonal_decomposed_trend':
    from statsmodels.tsa.seasonal import seasonal_decompose
    result = seasonal_decompose(y, model='multiplicative', freq=seaonsal_decomposition_freq)
    y2 = pd.Series(result.trend).ffill().bfill().values  # brutal extrapolation, y
    y3 = y - y2

# single-sided amplitude spectrum
spectrum = abs(np.fft.fft(y3))[:n//2]  # n, just for looking-good scaling
frequency = np.fft.fftfreq(n, d=1)[:n//2]
if n_sigma_cut is not None:
    m, s = np.mean(spectrum), np.std(spectrum)
    cut = m + s * n_sigma_cut
    mask = spectrum > cut
    spectrum = spectrum[mask]
    frequency = frequency[mask]

# TODO: predict using prioritized frequency, 2018.11.27

import matplotlib.pyplot as plt
import os
fig, ax = plt.subplots(2, 1)
title = os.path.basename(__file__)
fig.suptitle(title, fontsize='large')
fig.canvas.manager.set_window_title(title)

ax[0].plot(x, y, 'g')
ax[0].plot(x, y2, 'b')
ax[0].set_xlabel('time')
ax[0].set_ylabel('signal')
ax0t = ax[0].twinx()
ax0t.plot(x, y3, 'r', alpha=0.5)
ax0t.set_ylabel('noise')
if False:
    ax[1].plot(frequency, spectrum)
else:
    color = 'r'
    for f, s in zip(frequency, spectrum):
        ax[1].plot([f, f], [0, s], color, linestyle='-', alpha=0.7)
        ax[1].plot(f, s, color, marker='^')
ax[1].set_xlabel('frequency, f')
ax[1].set_ylabel('|Y(f)|')
plt.show()


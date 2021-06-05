"""
y, 2020.12.14
scipy.signal - psd.py
https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.welch.html
https://matplotlib.org/gallery/lines_bars_and_markers/psd_demo.html
"""

from scipy import signal
import matplotlib.pyplot as plt
import numpy as np

np.random.seed(1234)

fs = 10e3
N = 1e5
amp = 2 * np.sqrt(2)
freq = 1234.0
noise_power = 0.001 * fs / 2
time = np.arange(N) / fs
x = amp * np.sin(2 * np.pi * freq * time)
x += np.random.normal(scale=np.sqrt(noise_power), size=time.shape)

f, Pxx_den = signal.welch(x, fs, nperseg=1024)
plt.semilogy(f, Pxx_den)
plt.ylim([0.5e-3, 1])
plt.xlabel('frequency [Hz]')
plt.ylabel('PSD [V**2/Hz]')
plt.show()

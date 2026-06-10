"""
y, 2021.6.11
numpy - hillbert.py
https://stackoverflow.com/questions/30889748/how-to-obtain-sound-envelope-using-python
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import hilbert, chirp

duration = 1.0
fs = 400.0
samples = int(fs * duration)
t = np.arange(samples) / fs

signal = chirp(t, 20.0, t[-1], 100.0)
signal *= (1.0 + 0.5 * np.sin(2.0 * np.pi * 3.0 * t))

analytic_signal = hilbert(signal)
amplitude_envelope = np.abs(analytic_signal)

plt.plot(t, signal, label='signal')
plt.plot(t, amplitude_envelope, label='envelope')
plt.show()

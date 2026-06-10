"""
y, numpy - weiner filter.py, 2019.3.13

Reference
---------
[1] https://dsp-nbsphinx.readthedocs.io/en/nbsphinx-experiment/random_signals_LTI_systems/wiener_filter.html
[2] https://stackoverflow.com/questions/12851208/how-to-detect-significant-change-trend-in-a-time-series-data/13660660
[3] https://en.wikipedia.org/wiki/Least_mean_squares_filter

Lesson
------
[2] You can use a wiener filter if you know the signal statistics and use it as a n-step ahead predictor. Your decision
of trend can then easily be based on the prediction of the wiener filter. If the signal is not wide-sense stationary
and you think that prediction cannot be done linearly (a nonlinear/ nonstationary process) then you can use an adaptive
wiener filter like the LMS filter.
[3] LMS (Least Mean Squares) filter
"""

import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sig

N = 8129  # number of samples
M = 256  # length of Wiener filter
Om0 = 0.1*np.pi  # frequency of original signal
N0 = 0.1  # PSD of additive white noise

# generate original signal
s = np.cos(Om0 * np.arange(N))
# generate observed signal
g = 1/20*np.asarray([1, 2, 3, 4, 5, 4, 3, 2, 1])
n = np.random.normal(size=N, scale=np.sqrt(N0))
x = np.convolve(s, g, mode='same') + n
# estimate (cross) PSDs using Welch technique
f, Pxx = sig.csd(x, x, nperseg=M)
f, Psx = sig.csd(s, x, nperseg=M)
# compute Wiener filter
H = Psx/Pxx
H = H * np.exp(-1j*2*np.pi/len(H)*np.arange(len(H))*(len(H)//2))  # shift for causal filter
h = np.fft.irfft(H)
# apply Wiener filter to observation
y = np.convolve(x, h, mode='same')

# plot (cross) PSDs
Om = np.linspace(0, np.pi, num=len(H))

plt.figure(figsize=(10, 4))
plt.subplot(121)
plt.plot(Om, 20*np.log10(np.abs(.5*Pxx)), label=r'$| \Phi_{xx}(e^{j \Omega}) |$ in dB')
plt.plot(Om, 20*np.log10(np.abs(.5*Psx)), label=r'$| \Phi_{sx}(e^{j \Omega}) |$ in dB')
plt.title('(Cross) PSDs')
plt.xlabel(r'$\Omega$')
plt.legend()
plt.axis([0, np.pi, -60, 40])
plt.grid()

# plot transfer function of Wiener filter
plt.subplot(122)
plt.plot(Om, 20*np.log10(np.abs(H)))
plt.title('Transfer function of Wiener filter')
plt.xlabel(r'$\Omega$')
plt.ylabel(r'$| H(e^{j \Omega}) |$ in dB')
plt.axis([0, np.pi, -150, 3])
plt.grid()
plt.tight_layout()

# plot signals
idx = np.arange(500, 600)
plt.figure(figsize=(10, 4))
plt.plot(idx, x[idx], label=r'observed signal $x[k]$')
plt.plot(idx, s[idx], label=r'original signal $s[k]$')
plt.plot(idx, y[idx], label=r'estimated signal $y[k]$')
plt.title('Signals')
plt.xlabel(r'$k$')
plt.axis([idx[0], idx[-1], -1.5, 1.5])
plt.legend()
plt.grid()

plt.show()
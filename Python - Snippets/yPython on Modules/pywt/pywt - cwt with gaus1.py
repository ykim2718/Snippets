"""
y, pywt - cwt with gaus1.py, 2019.9.15, 11.12; 2021.1.8
https://pywavelets.readthedocs.io/en/latest/ref/cwt.html#single-level-cwt
https://pywavelets.readthedocs.io/en/latest/ref/wavelets.html#wavelet-families
"""

import pywt
import numpy as np
import matplotlib.pyplot as plt

x = np.arange(512)
y = np.sin(2 * np.pi * x / 32)
# Working: gaus1, mexh, morl
# Non-Working: haar, db, sym, coif, bior, rbio, dmey, gaus, cgau, shan, fbsp, cmor,
#              cmorB-C, gausP, cgauP, shanB-C, fpspM-B-C
coef, freqs = pywt.cwt(y, np.arange(1, 129), pywt.ContinuousWavelet('haar'))
print(coef.shape)  # (128, 512)
print(freqs.shape)  # (128,)
plt.matshow(coef)  # doctest: +SKIP
plt.show()  # doctest: +SKIP

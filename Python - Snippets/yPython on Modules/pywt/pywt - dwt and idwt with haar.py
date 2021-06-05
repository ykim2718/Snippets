"""
y, 2021.1.27
pywt - dwt and idwt with haar.py
https://youtu.be/Qryd7z9k8i4  >> Wavelet Transform Analysis of 1-D signals using Python
https://community.backtrader.com/topic/1312/haar-wavelet-with-lifting-and-incremental-option  ★
https://pywavelets.readthedocs.io/en/latest/ref/signal-extension-modes.html#ref-modes
"""

import pywt

x = [3, 7, 1, 1, -2, 5, 4, 6]  # signal
cA, cD = pywt.dwt(x, 'haar')  # wavelet transform
y = pywt.idwt(cA, cD, 'haar')  # inverse wavelet transform

print(f"x={x}")  # signal
print(f"cA={cA}")  # approximation coeffs
print(f"cD={cD}")  # detailed coeffs
print(f"y={y}")  # reconstructed signal

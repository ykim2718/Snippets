"""
y, 2021.1.27
pywt - wavedec and waverec.py
https://youtu.be/Qryd7z9k8i4  >> Wavelet Transform Analysis of 1-D signals using Python
"""

import pywt

x = [3, 7, 1, 1, -2, 5, 4, 6, 6, 4, 5, -2, 1, 1, 7, 3]  # signal
wavelet = 'haar'  # db1
coeffs = pywt.wavedec(x, wavelet, level=2, mode='periodic')  # DWT, decomposition
cA2, cD2, cD1 = coeffs
y = pywt.waverec(coeffs, wavelet, mode='periodic')  # IDWT, reconstruction

print(f"x={x}")  # signal
print(f"cA2={cA2}")  # approximation coeffs
print(f"cD2={cD2}")  # detailed coeffs
print(f"cD1={cD1}")  # detailed coeffs
print(f"y={y}")  # reconstructed signal


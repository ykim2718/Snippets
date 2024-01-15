"""
y, 2024.1.15
sklearn - minmax scaler partial_fit.py
"""

from sklearn.preprocessing import MinMaxScaler
import numpy as np

a = np.arange(12).reshape(4, 3)
a = a.astype('float32')
print(f"{a=}")
print(f"{a.shape=}, {a.min()=}, {a.max()=}")

scaler = MinMaxScaler(*tuple(), **dict())
scaler.fit(a)
print(f"fit:\n{scaler.transform(a)=}")

scaler = MinMaxScaler()
scaler.partial_fit(a[0:2])
print(f"partial_fit:\n{scaler.transform(a)=}")
scaler.partial_fit(a[2:4])
print(f"partial_fit:\n{scaler.transform(a)=}")


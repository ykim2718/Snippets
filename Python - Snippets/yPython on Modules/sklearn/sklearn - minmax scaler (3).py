"""
y, 2020.1.9
sklearn - minmax scaler (3).py
"""

from sklearn.preprocessing import MinMaxScaler
import numpy as np

a = np.arange(48).reshape(4, 3, 2, 2)  # sample, width, length, channel
a = a.astype('float32')
# print(a)
print(a.shape, a.min(), a.max())
for j in range(a.shape[0]):
    b = a[j]
    b = b.reshape(a.shape[1] * a.shape[2], -1)
    c = MinMaxScaler().fit_transform(b)
    c = c.reshape(*a.shape[1:])
    a[j] = c
print(a.shape, a.min(), a.max())

"""
y, 2020.7.9
numpy - rolling window.py
https://stackoverflow.com/questions/6811183/rolling-window-for-1d-arrays-in-numpy/6811241#6811241
"""

import numpy as np


def rolling_window(array, window, stride=1):
    shape = array.shape[:-1] + (array.shape[-1] - window + 1, window)
    strides = array.strides + (array.strides[-1],)
    print(shape, strides)
    return np.lib.stride_tricks.as_strided(array, shape=shape, strides=strides)


a = np.arange(9)
for b in rolling_window(a, 4):
    print(b)

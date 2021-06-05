"""
y, numpy - rolling mean.py, 2018.7.21
https://stackoverflow.com/questions/13728392/moving-average-or-running-mean/27681394
"""

import numpy as np

a = [1, 2, 3, 4]
n = 2
rm = np.convolve(a, np.ones((n,))/n, mode='valid')
print(rm)


def yRollingMean(a, n=1, keep_dim=True):
    """ y, 2018.7.21 """

    if n <= len(a):
        rm = np.convolve(a, np.ones((n,))/n, mode='valid')
        if keep_dim:
            rm = np.concatenate([a[:n-1], rm])
    else:
        rm = a
    return rm


print('a=', a)
print('n=1', yRollingMean(a, 1))
print('n=2', yRollingMean(a, 2))
print('n=3', yRollingMean(a, 3))
print('n=4', yRollingMean(a, 4))
print('n=4', yRollingMean(a, 4, False))
print('n=5', yRollingMean(a, 5))

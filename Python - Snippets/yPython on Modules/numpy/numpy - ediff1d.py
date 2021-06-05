"""
y, numpy - ediff1d.py, 2018.7.21
https://docs.scipy.org/doc/numpy/reference/generated/numpy.ediff1d.html#numpy.ediff1d
"""

a = [0, 1, 3, 6, 10]


import numpy as np

def yElemDifference1D(a, n=1):
    """ y, 2018.7.19 - 21 """

    assert isinstance(a, (list, np.ndarray))
    assert n >= 1

    a = np.array(a)

    t = len(a)
    d1 = a[1:] - a[:-1]  # assert len(d1) = (t-1)
    d1 = np.pad(d1, (1, 0), 'reflect', reflect_type='odd')  # assert len(d1) == t
    ds = np.empty((n, t))
    ds[0] = d1
    for j in range(2, n+1, 1):
        d = a[j:] - a[:-j]
        ds[j-1] = np.concatenate([ds[j-2][:j], d])
    return np.mean(ds, axis=0)


print('a=', a)
print('n=1', yElemDifference1D(a, 1))
print('n=2', yElemDifference1D(a, 2))
print('n=3', yElemDifference1D(a, 3))

print('ediff1d=', np.ediff1d(a))
print('ediff1d=', np.ediff1d(a, to_begin=a[1]-a[1]/2))
print('ediff1d=', np.ediff1d(np.array(a).astype(float), to_begin=(a[1]-a[0])/2))

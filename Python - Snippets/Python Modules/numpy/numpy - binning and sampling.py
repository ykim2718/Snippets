"""
y, 2020.1.21
numpy - binning and sampling.py
https://docs.scipy.org/doc/numpy/reference/generated/numpy.digitize.html
"""

import numpy as np

x = np.random.normal(50, 10, size=100)
# print(f"x={x}")
bins = np.linspace(x.min(), x.max(), 9)  # increasing order
print(f"bins={bins}")
inds = np.digitize(x, bins)
np.place(inds, inds == bins.size, [bins.size - 1])
print(f"inds={inds}, inds.size={inds.size}")
unique, counts = np.unique(inds, return_counts=True)
print(f"unique={unique}, counts={counts}")
sample_size = 50
k = sample_size // bins.size
for j in range(k, counts.max() + 1):
    sampling = np.array([j if j <= c else c for c in counts])
    total = sampling.sum()
    if sample_size == total:
        print(f"j={j}, sampling={sampling}, sampling.sum()={sampling.sum()}")
        break
    elif sample_size < total:
        extra = total - sample_size
        print(f"j={j}, sampling={sampling}, sampling.sum()={sampling.sum()}, extra={extra}")
        mask = sampling == j
        mask[mask] = np.random.permutation([True] * extra + [False] * (np.sum(mask) - extra))
        np.place(sampling, mask, [j-1])
        print(f"j={j}, sampling={sampling}, sampling.sum()={sampling.sum()}")
        break
assert sum(sampling) == sample_size,\
    f"expected sum(sampling) == sample_size but got sum(sampling)={sum(sampling)} Vs sample_size={sample_size}"


"""
bins=[20.64659007 27.79439285 34.94219563 42.08999841 49.2378012  56.38560398
 63.53340676 70.68120954 77.82901232]
inds=[3 6 5 3 2 3 5 3 5 7 3 7 3 3 5 6 4 3 6 4 4 4 4 4 5 4 4 8 4 4 4 6 5 3 3 2 5
 4 4 5 6 3 6 4 6 5 5 5 4 6 2 4 2 4 4 2 5 3 3 2 5 4 4 4 5 3 3 6 7 5 8 1 6 2
 3 3 3 2 3 7 4 5 6 4 4 6 6 5 7 4 5 3 3 6 3 5 7 7 5 4], inds.size=100
unique=[1 2 3 4 5 6 7 8], counts=[ 1  8 22 26 20 14  7  2]
j=8, sampling=[1 8 8 8 8 8 7 2], sampling.sum()=50
"""

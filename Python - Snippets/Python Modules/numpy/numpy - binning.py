"""
y, 2020.1.20
numpy - binning.py
https://docs.scipy.org/doc/numpy/reference/generated/numpy.digitize.html
"""

import numpy as np

x = np.array([0.2, 6.4, 3.0, 1.6, 6.3, 5])
print(f"x={x}")
bins = np.linspace(x.min(), x.max(), 5)  # increasing order
print(f"bins={bins}")
inds = np.digitize(x, bins)
print(f"inds={inds}")
for j in range(x.size):
    k = inds[j]
    if k == bins.size:
        print(f"inds[{j}]={k}:", bins[k - 1], "<=", x[j])
    else:
        print(f"inds[{j}]={k}:", bins[k - 1], "<=", x[j], "<", bins[k])

"""
x=[0.2 6.4 3.  1.6 6.3 5. ]
bins=[0.2  1.75 3.3  4.85 6.4 ]
inds=[1 5 2 1 4 4]
inds[0]=1: 0.2 <= 0.2 < 1.75
inds[1]=5: 6.4 <= 6.4
inds[2]=2: 1.75 <= 3.0 < 3.3000000000000003
inds[3]=1: 0.2 <= 1.6 < 1.75
inds[4]=4: 4.8500000000000005 <= 6.3 < 6.4
inds[5]=4: 4.8500000000000005 <= 5.0 < 6.4
"""

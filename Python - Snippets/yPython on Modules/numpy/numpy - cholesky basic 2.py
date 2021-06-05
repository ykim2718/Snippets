"""
y, 2020.9.19
numpy - cholesky basic 2.py
https://blogs.sas.com/content/iml/2012/02/08/use-the-cholesky-transformation-to-correlate-and-uncorrelate-variables.html
"""

import numpy as np

x = np.random.normal(loc=0.0, scale=1.0, size=1000)
y = np.random.normal(loc=0.0, scale=1.0, size=1000)
xy = np.stack([x, y])
print(f"xy.shape={xy.shape}")

L = np.array([[3, 1], [1, 1]])
xy = L * xy

import matplotlib.pyplot as plt


fig = plt.figure()
ax1 = fig.add_subplot()

ax1.scatter(x, y, marker='o', c='r', s=20, linewidths=1, alpha=0.5)

plt.show()
xxx

def is_pos_def(x):
    return np.all(np.linalg.eigvals(x) > 0)


print(f"positive definite={is_pos_def(a)}")

L = np.linalg.cholesky(a)
print(f"cholesky matrix=\n{L}")

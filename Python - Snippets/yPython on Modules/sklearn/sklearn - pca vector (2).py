"""
y, sklearn - pca vector (2).py, 2020.4.15
https://stackoverflow.com/questions/22984335/recovering-features-names-of-explained-variance-ratio-in-pca-with-sklearn
https://matplotlib.org/api/_as_gen/matplotlib.pyplot.annotate.html
please refer to 'mpl - PCA arrows.py' as benchmarking, 2020.4.15
"""

print(__doc__)

import numpy as np
import sklearn as sk
import sklearn.decomposition as sk_decomposition
import pandas as pd
import matplotlib.pyplot as plt
import pathlib

ss = 1000
x_true = np.linspace(0, 500, ss)
y_true = 1.5 * x_true
x = x_true + np.random.normal(0, 100, ss)
y = y_true + np.random.normal(0, 100, ss)
x = np.reshape(x, (ss, 1))
y = np.reshape(y, (ss, 1))
print(f"x.shape={x.shape}")  # (1000, 1)
print(f"y.shape={y.shape}")  # (1000, 1)
array = np.hstack((x, y))
print(f"array.shape={array.shape}")  # (1000, 2)

# array = sk.preprocessing.scale(array)
pca = sk_decomposition.PCA(n_components=2)  # , random_state=777, svd_solver='full')
projected_array = pca.fit_transform(array)
print(f"projected_array.shape={projected_array.shape}")
mu = pca.mean_
sigma = projected_array.std(axis=0)
print(f"mu.shape={mu.shape}: {mu}")
print(f"sigma.shape={sigma.shape}: {sigma}")
eigenvectors = pca.components_ * +1
print(f"eigenvectors={eigenvectors}")

# print(pd.DataFrame(pca.components_, columns=list('xy'), index=['PC-1', 'PC-2']))


def arrow(ax1, start, end):
    arrow = ax1.annotate('', xy=end, xycoords='data', xytext=start, textcoords='data',
                         arrowprops=dict(facecolor='red', width=4.0))
    return arrow


title = pathlib.Path(__file__).name
fig, ax1 = plt.subplots()
fig.canvas.set_window_title(title)
fig.suptitle(title)
ax1.scatter(x, y)
for pc, s in zip(eigenvectors, sigma):
    arrow(ax1, mu, mu + s * pc)

ax1.set_aspect('equal')
xl = ax1.get_xlim()
yl = ax1.get_ylim()
limits = min(xl[0], yl[0]), max(xl[1], yl[1])
ax1.set_xlim(limits)
ax1.set_ylim(limits)

plt.show()


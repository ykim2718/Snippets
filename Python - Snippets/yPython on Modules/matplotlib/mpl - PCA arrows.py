"""
y, on Fri Nov 21 23:27:52 2014, 2020.4.15$
mpl - PCA arrows.py

Basic example for PCA with matplotlib
http://stackoverflow.com/questions/18299523/basic-example-for-pca-with-matplotlib
please refer to 'sklearn - pca vector (2).py' as benchmarking, 2020.4.15
"""

import numpy as np
import matplotlib.pyplot as plt
import pathlib

N = 1000
xTrue = np.linspace(0, 500, N)
yTrue = 1.5 * xTrue
xData = xTrue + np.random.normal(0, 100, N)
yData = yTrue + np.random.normal(0, 100, N)
xData = np.reshape(xData, (N, 1))
yData = np.reshape(yData, (N, 1))
data = np.hstack((xData, yData))
print(f"data.shape={data.shape}")

mu = data.mean(axis=0)
data = data - mu
# data = (data - mu)/data.std(axis=0)  # Uncomment this reproduces mlab.PCA results
eigenvectors, eigenvalues, V = np.linalg.svd(data.T, full_matrices=False)
projected_data = np.dot(data, eigenvectors)
print(f"projected_data.shape={projected_data.shape}")
# sigma = projected_data.std(axis=0).mean()  # y
sigma = projected_data.std(axis=0)
print(f"eigenvectors={eigenvectors}")
print(f"sigma={sigma}")


def annotate(ax, name, start, end):
    arrow = ax.annotate(name,
                        xy=end, xycoords='data',
                        xytext=start, textcoords='data',
                        arrowprops=dict(facecolor='red', width=2.0))
    return arrow


title = pathlib.Path(__file__).name
fig, ax1 = plt.subplots()
fig.canvas.manager.set_window_title(title)
fig.suptitle(title)
ax1.scatter(xData, yData)
for pc, s in zip(eigenvectors, sigma):
    annotate(ax1, '', mu, mu + s * pc)

ax1.set_aspect('equal')
xl = ax1.get_xlim()
yl = ax1.get_ylim()
limits = min(xl[0], yl[0]), max(xl[1], yl[1])
ax1.set_xlim(limits)
ax1.set_ylim(limits)

plt.show()

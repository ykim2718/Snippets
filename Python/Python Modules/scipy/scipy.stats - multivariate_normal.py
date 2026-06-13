"""
y, scipy.stats - multivariate_normal.py, 2018.12.15; 2019.11.11
https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.stats.multivariate_normal.html
"""

import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import multivariate_normal, mvn

mu, S = [-5, 5], [[1.2, 0], [0.2, 1]]
p1 = np.array([-5, 5])
p2 = np.array([100, 100])
p, i = mvn.mvnun(p1, p2, mu, S)
print(p)

x, y = np.mgrid[-10:0:.01, 0:10:.01]
print(x.shape)
print(y.shape)
pos = np.dstack((x, y))
dist = multivariate_normal(mean=mu, cov=S)
print(pos.shape)  # (1000, 1000, 2)
print(dist.pdf(pos).shape)  # (1000, 1000)

fig = plt.figure()
ax1 = fig.add_subplot(111)
ax1.contourf(x, y, dist.pdf(pos))
plt.show()




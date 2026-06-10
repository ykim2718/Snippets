"""
y, 2021.4.22
sklearn - DBSCAN 1d.py
https://stackoverflow.com/questions/56062673/clustering-the-3d-points-when-given-the-x-y-z-coordinates-using-dbscan-algorithm
https://stackoverflow.com/questions/53490812/simple-2-d-clustering-algorithm-in-python
https://scikit-learn.org/stable/modules/generated/sklearn.cluster.DBSCAN.html#sklearn.cluster.DBSCAN
"""

import numpy as np
from sklearn.cluster import DBSCAN

a = np.array([1, 2, 3, 6, 6, 9, 9, 9])
a = np.expand_dims(a, axis=1)
model = DBSCAN(eps=2, min_samples=2)
model.fit_predict(a)
print("number of cluster found: {}".format(len(set(model.labels_))))
print("cluster for each point: {}".format(model.labels_))


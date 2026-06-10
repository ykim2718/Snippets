"""
y, sklearn - standard scaler.py, 2018.12.10
https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.StandardScaler.html
"""

from sklearn.preprocessing import StandardScaler

data = [[-1, 2], [-0.5, 6], [0, 10], [1, 18]]
scaler = StandardScaler()
print(scaler.fit(data))
print(scaler.mean_)
print(scaler.transform(data))
print(scaler.transform([[2, 2]]))

transformed = scaler.transform(data)
inversed = scaler.inverse_transform(transformed)
print(inversed)

import numpy as np
print(np.mean(transformed, axis=0), np.std(transformed, axis=0))

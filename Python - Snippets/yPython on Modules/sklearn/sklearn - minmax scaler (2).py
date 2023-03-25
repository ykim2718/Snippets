"""
y, sklearn - min_max scaler (2).py, 2019.3.25, 12.10
https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
"""

from sklearn.preprocessing import MinMaxScaler
import numpy as np

data = np.array([[-1, 2], [-0.5, 6], [0, 10], [1, 18]])
scaler = MinMaxScaler()

if True:
    for row in data:
        # print(row)
        scaler.partial_fit(row[np.newaxis, :])
else:
    print(scaler.fit(data))

print(scaler.data_max_)
print(scaler.transform(data))
print(scaler.transform([[2, 2]]))

transformed = scaler.transform(data)
inversed = scaler.inverse_transform(transformed)
print(inversed, np.array_equal(data, inversed))



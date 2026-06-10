"""
y, sklearn - min_max scaler.py, 2018.12.10
https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
"""

from sklearn.preprocessing import MinMaxScaler

data = [[-1, 2], [-0.5, 6], [0, 10], [1, 18]]
scaler = MinMaxScaler()
print(scaler.fit(data))
print(scaler.data_max_)
print(scaler.transform(data))
print(scaler.transform([[2, 2]]))

transformed = scaler.transform(data)
inversed = scaler.inverse_transform(transformed)
print(inversed)



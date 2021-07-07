"""
y, sklearn - sv regression.py,
2018.12.7; 2021.6.25
https://archive.ics.uci.edu/ml/datasets/wine << Machine Learning Data Repository
"""

from sklearn.svm import SVR
from sklearn.metrics import r2_score
import numpy as np
import pandas as pd
import pathlib

# set parameter
model_name = SVR
train_rate = 0.7
k_type = 'rbf'  #  [linear, poly, rbf, sigmoid]
d_value = 3  # [1, 2, 3, 4, 5]  # only for poly kernel
c_value = 100

# get data
data_folder = pathlib.Path(f"d:\HA\yStudy on code - Python\Python - Snippets\yPython on Machine Learning\Data")
# raw_data = np.genfromtxt(r'..\data\bike_sharing.csv', delimiter=',', skip_header=1)
frame = pd.read_csv(
    data_folder / 'UC Irvine Machine Learning Repository - Bike Sharing/hour.csv',
    usecols=['temp', 'atemp', 'hum', 'windspeed', 'cnt']
)
raw_data = frame.values
n_data, n_column = raw_data.shape

# set train and test

# set train and test
n_train = int(n_data * train_rate)
train_index = range(n_train)
test_index = range(n_train, n_data)
train, test = raw_data[train_index,], raw_data[test_index,]
train_x, train_y = train[:, :(n_column-1)], train[:, n_column-1]
test_x, test_y = test[:, :(n_column-1)], test[:, n_column-1]

# select model
model = model_name(kernel=k_type, degree=d_value, C=c_value)

# train model
model.fit(train_x, train_y)

# eval
train_perf = r2_score(train_y, model.predict(train_x))
test_perf = r2_score(test_y, model.predict(test_x))

print("performance of train data is %.4f, while that of test data is %.4f" % (train_perf, test_perf))

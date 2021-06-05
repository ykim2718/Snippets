"""
y, sklearn - sv classification.py, 2018.12.7
https://archive.ics.uci.edu/ml/datasets/wine+quality << Machine Learning Data Repository
"""

from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
import numpy as np
import pandas as pd

# set parameter
model_name = SVC
train_rate = 0.7
k_type = 'rbf'  #  [linear, poly, rbf, sigmoid]
d_value = 3  # [1, 2, 3, 4, 5]  # only for poly kernel
c_value = 1.0  # [0.01, 0.1, 1, 10, 100]
dfs_type = 'ovr'  # [ovr, ovo]

# get data
# raw_data = np.genfromtxt(r'..\data\UC Irvine Machine Learning Repository - Wine\wine.csv', delimiter=',', skip_header=1)
frame = pd.read_csv(r'..\data\UC Irvine Machine Learning Repository - Wine\winequality-red.csv', delimiter=';')
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
model = model_name(kernel=k_type, degree=d_value, C=c_value, decision_function_shape=dfs_type)

# train model
model.fit(train_x, train_y)

# eval
train_perf = accuracy_score(train_y, model.predict(train_x))
test_perf = accuracy_score(test_y, model.predict(test_x))

print("performance of train data is %.4f, while that of test data is %.4f" % (train_perf, test_perf))

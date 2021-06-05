"""
y, sklearn - Lec2_4 simple linear regression.p, 2018.12.8
https://ratsgo.github.io/natural%20language%20processing/2017/08/16/deepNLP/  << Machine Learning Data Repository
"""

from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score
import numpy as np
import pandas as pd

# set parameter
model_name = LinearRegression
var_list = [1]
train_rate = 0.6

# get data
# raw_data = np.genfromtxt(r"..\data\bike-sharing-hour.csv", delimiter=',', skip_header=1)
frame = pd.read_csv(r'..\data\UC Irvine Machine Learning Repository - Bike Sharing\hour.csv',
                    usecols=['temp', 'atemp', 'hum', 'windspeed', 'cnt'])
raw_data = frame.values
print(raw_data.shape)
n_data, n_column = raw_data.shape

# set train and test
n_train = int(n_data * train_rate)
train_index = range(n_train)
test_index = range(n_train, n_data)
train, test = raw_data[train_index,], raw_data[test_index,]
train_x, train_y = train[:, var_list], train[:, (n_column - 1)]
test_x, test_y = test[:, var_list], test[:, (n_column - 1)]

# set model
model = model_name()

# train model
model.fit(train_x, train_y)

# eval
train_perf = r2_score(train_y, model.predict(train_x))
test_perf = r2_score(test_y, model.predict(test_x))

print("performance of train data is %.4f, while that of test data is %.4f" % (train_perf, test_perf))

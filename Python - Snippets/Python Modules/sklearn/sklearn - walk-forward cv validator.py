"""
y, sklearn - walk-forward cv validator.py, 2018.12.2

Reference
---------
[1] https://machinelearningmastery.com/backtest-machine-learning-models-time-series-forecasting/
[2] https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.TimeSeriesSplit.html

Note
----
[1] k-fold cross validation cannot be directly used with time series data.
This is because they assume that there is no relationship between the observations, that each observation
is independent. This is not true of time series data, where the time dimension of observations means that
we cannot randomly split them into groups. Instead, we must split data up and respect the temporal order
in which values were observed.

"""


import numpy as np
from sklearn.model_selection import TimeSeriesSplit

n_samples, n_features = 4, 2

X = np.arange(n_samples*n_features).reshape(n_samples, n_features)
Y = np.arange(n_samples)
print(X, Y)
print(X.shape, Y.shape)

k_fold = n_samples - 1
f = TimeSeriesSplit(n_splits=k_fold)
print(f)

for j, (train_index, test_index) in enumerate(f.split(X, Y), start=1):
    print(j, dict(train=(X[train_index], Y[train_index]), test=(X[test_index], Y[test_index])))



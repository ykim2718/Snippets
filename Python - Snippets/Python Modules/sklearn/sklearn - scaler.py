"""
y, sklearn - scaler.py, 2018.11.23, 11.25
"""

import numpy as np
from sklearn.preprocessing import MinMaxScaler

a = np.random.randint(10, size=10).reshape(-1, 2)
print(a)
print(a.shape)

scaler = MinMaxScaler(feature_range=(0, 1))
transformed = scaler.fit_transform(a)
print(transformed.shape)

inversed = scaler.inverse_transform(transformed)
print(inversed.shape)
print(np.concatenate([a.T, transformed.T, inversed.T]).T)

# save scaler
# 2018.11.25
# https://stackoverflow.com/questions/41993565/save-minmaxscaler-model-in-sklearn

import os
scaler_file_name = os.path.splitext(os.path.basename(__file__))[0] + '.save'

from sklearn.externals import joblib

joblib.dump(scaler, scaler_file_name)

# And now to load...

scaler = joblib.load(scaler_file_name)


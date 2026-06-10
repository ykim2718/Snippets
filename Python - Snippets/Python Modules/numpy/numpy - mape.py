"""
y, numpy - mape.py, 2018.11.29
https://stats.stackexchange.com/questions/58391/mean-absolute-percentage-error-mape-in-scikit-learn
"""

import numpy as np

def mean_absolute_percentabe_error(y_true, y_pred):
    """ y, 2018.11.29 """

    y_true, y_pred = np.array(y_true), np.array(y_pred)
    mask = (y_true > 0) & (y_pred > 0)
    y_true, y_pred = y_true[mask], y_pred[mask]
    mape = np.mean(np.abs((y_true - y_pred)/y_true)) * 100
    return mape

y_true = [3, 0.0, 2, 7]; y_pred = [2.5, -0.3, 2, 8]
mape = mean_absolute_percentabe_error(y_true, y_pred)
print(mape)


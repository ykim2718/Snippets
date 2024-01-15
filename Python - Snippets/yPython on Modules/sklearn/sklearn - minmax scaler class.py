"""
y, sklearn - min_max scaler class.py, 2018.12.12; 2024.1.15
https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html
"""

import sklearn.preprocessing as skl_preprocessing
import numpy as np


class MinMaxScalerEx(skl_preprocessing.MinMaxScaler):
    """ y, 2018.12.12 """

    def __init__(self, keep_sign=False, **kwargs):
        """
        y,  2019.11.17
            2024.1.15
        """

        self.keep_sign = bool(keep_sign)
        super().__init__(**kwargs)

    def transform_y(self, y, y_anchor_location):  # y_anchor_location: y loc in x columns
        """ y, 2018.12.12 """

        y = np.array(y).astype(float)
        y *= self.scale_[y_anchor_location]
        y += self.min_[y_anchor_location]
        return y

    def inverse_transform_y(self, y, y_anchor_location):
        """ y,2018.12.12 """

        y = np.array(y).astype(float)
        y -= self.min_[y_anchor_location]
        y /= self.scale_[y_anchor_location]
        return y


X = [[-1, 2], [-0.5, 6], [0, 10], [1, 18]]
Y = [1, 2, 3, 4]
scaler = MinMaxScalerEx()
scaler.fit(X)
X_t = scaler.transform(X)
Y_t = scaler.transform_y(Y, 0)
print(X_t, Y_t)
X_i = scaler.inverse_transform(X_t)
Y_i = scaler.inverse_transform_y(Y_t, 0)
print(X_i, Y_i)


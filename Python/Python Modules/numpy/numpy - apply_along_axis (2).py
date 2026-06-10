"""
y, 2022.8.27
numpy - apply_along_axis (2).py
https://numpy.org/doc/stable/reference/generated/numpy.apply_along_axis.html
"""

import numpy as np
from sklearn import preprocessing


a = np.arange(120).reshape((2, 3, 4, 5))
print(f"{a[0][0]=}")
print(f"{a.shape=}")  # a.shape=(2, 3, 4, 5)


def scale_to_0_1(v, scaler=preprocessing.MinMaxScaler()):
    assert isinstance(v, np.ndarray)
    assert v.shape == (4,)
    v = np.expand_dims(v, axis=-1)
    v = scaler.fit_transform(v)
    v = np.squeeze(v)
    return v


b = np.apply_along_axis(scale_to_0_1, 2, a)
print(f"{b[0][0]=}")
print(f"{b[-1][0]=}")


"""
a[0][0]=array([[ 0,  1,  2,  3,  4],
       [ 5,  6,  7,  8,  9],
       [10, 11, 12, 13, 14],
       [15, 16, 17, 18, 19]])
a.shape=(2, 3, 4, 5)
b[0][0]=array([[0.        , 0.        , 0.        , 0.        , 0.        ],
       [0.33333333, 0.33333333, 0.33333333, 0.33333333, 0.33333333],
       [0.66666667, 0.66666667, 0.66666667, 0.66666667, 0.66666667],
       [1.        , 1.        , 1.        , 1.        , 1.        ]]
b[-1][0]=array([[0.        , 0.        , 0.        , 0.        , 0.        ],
       [0.33333333, 0.33333333, 0.33333333, 0.33333333, 0.33333333],
       [0.66666667, 0.66666667, 0.66666667, 0.66666667, 0.66666667],
       [1.        , 1.        , 1.        , 1.        , 1.        ]])
"""

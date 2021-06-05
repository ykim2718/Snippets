"""
y, sklearn - train_test_split (2).py, 2018.11.28
https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html ★
"""

import numpy as np
from sklearn.model_selection import train_test_split

batch_count, batch_size, feature_count = 5, 3, 2

X = np.arange(batch_count*batch_size*feature_count).reshape((batch_count, batch_size, feature_count))
y = np.arange(batch_count*batch_size).reshape(batch_count, batch_size)
print(dict(X=X, y=y))
print('shape=', dict(X=X.shape, y=y.shape))
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=77)
print(dict(X_train=X_train, y_train=y_train))
print(dict(X_test=X_test, y_test=y_test))



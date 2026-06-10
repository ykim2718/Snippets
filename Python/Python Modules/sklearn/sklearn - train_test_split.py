"""
y, sklearn - train_test_split.py, 2018.11.26, 11.28
https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html ★
"""

import numpy as np
from sklearn.model_selection import train_test_split

n_samples, n_features = 5, 2

X, y = np.arange(n_samples*n_features).reshape((n_samples, n_features)), np.arange(n_samples)
print(dict(X=X, y=y))
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
print(dict(X_train=X_train, y_train=y_train))
print(dict(X_test=X_test, y_test=y_test))



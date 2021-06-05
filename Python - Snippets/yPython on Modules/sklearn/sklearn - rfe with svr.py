"""
y, sklearn - rfe with svr.py, 2018.12.18
https://scikit-learn.org/stable/modules/generated/sklearn.feature_selection.RFE.html
https://scikit-learn.org/stable/modules/generated/sklearn.datasets.make_friedman1.html
"""

from sklearn.datasets import make_friedman1
from sklearn.feature_selection import RFE
from sklearn.svm import SVR

X, y = make_friedman1(n_samples=50, n_features=10, random_state=0)
print(X.shape)
print(y.shape)

n_features = 5  # The number of features to select. If None, half of the features are selected.
n_steps_per_iteration = 1  # The (integer) number of features to remove at each iteration.

estimator = SVR(kernel="linear")
selector = RFE(estimator, n_features_to_select=n_features, step=n_steps_per_iteration)
selector = selector.fit(X, y)

print(selector.support_)  # array([ True,  True,  True,  True,  True, False, False, False, False, False])
print(selector.ranking_)  # array([1, 1, 1, 1, 1, 6, 4, 3, 2, 5])


"""
y, sklearn - k-fold cv validator.py, 2018.11.28, 12.1
https://machinelearningmastery.com/evaluate-performance-deep-learning-models-keras/
https://www.kaggle.com/stefanie04736/simple-keras-model-with-k-fold-cross-validation
https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.KFold.html
"""

import numpy as np
from sklearn.model_selection import KFold, StratifiedKFold, RepeatedStratifiedKFold

n_samples, n_features = 4, 2
folder = 'StratifiedKFold'
folder = 'RepeatedStratifiedKFold'
folder = 'KFold'

X = np.arange(n_samples*n_features).reshape(n_samples, n_features)
y = np.arange(n_samples)
if folder in ['StratifiedKFold', 'RepeatedStratifiedKFold']:
    y = np.array([0, 0, 1, 1])
print(X.shape, y.shape)

if folder == 'KFold':
    k_fold = n_samples
    k_fold = 2
    f = KFold(n_splits=k_fold, random_state=None, shuffle=False)
elif folder == 'StratifiedKFold':
    n_unique = len(np.unique(y))
    assert n_unique > 1 and (len(y) % n_unique) == 0
    f = StratifiedKFold(n_splits=n_unique, random_state=None, shuffle=False)
elif folder == 'RepeatedStratifiedKFold':
    n_unique = len(np.unique(y))
    assert n_unique > 1 and (len(y) % n_unique) == 0
    f = RepeatedStratifiedKFold(n_splits=n_unique, n_repeats=n_samples, random_state=None)

for j, (train_index, test_index) in enumerate(f.split(X, y), start=1):
    print(j, dict(train=X[train_index], test=X[test_index]))

"""
y, sklearn - predefined split.py, 2018.12.2
https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.PredefinedSplit.html
"""

from sklearn.model_selection import PredefinedSplit
import numpy as np

X = np.array([[1, 2], [3, 4], [1, 2], [3, 4]])
y = np.array([0, 0, 1, 1])
test_fold = [0, 1, -1, 1]
ps = PredefinedSplit(test_fold)
ps.get_n_splits()
print(ps)
for train_index, test_index in ps.split():
    print("TRAIN:", train_index, "TEST:", test_index)
"""
y, sklearn - variance threshold.py, 2019.10.13
[1] https://www.kaggle.com/bertcarremans/data-preparation-exploration
[2] https://scikit-learn.org/stable/modules/generated/sklearn.feature_selection.VarianceThreshold.html
[3] https://datascienceschool.net/view-notebook/bf8d9a70e92b48c2853449ec175c55ab
"""

import pandas as pd
from sklearn.feature_selection import VarianceThreshold


X = [[0, 2, 0, 3], [0, 1, 4, 3], [0, 1, 1, 3]]
frame = pd.DataFrame(X, columns=list('abcd'))
print(frame)
selector = VarianceThreshold(threshold=0.0)
if False:
    selected = selector.fit_transform(X)
    print(selected)
else:
    selector.fit(frame)
    selected = selector.get_support()
    print(selected)
    print(frame[frame.columns[selected]])
"""
y, sklearn - r2.py, 2019.10.18
https://scikit-learn.org/stable/modules/generated/sklearn.metrics.r2_score.html
https://www.techwalla.com/articles/how-to-calculate-r2-excel
https://en.wikipedia.org/wiki/Root_mean_square
https://stackoverflow.com/questions/45250100/kerasregressor-coefficient-of-determination-r2-score  ★★
"""


import sklearn.metrics as sk_metrics

y_true = [3, -0.5, 2, 7]
y_pred = [2.5, 0.0, 2, 8]
r2 = sk_metrics.r2_score(y_true, y_pred)
print(r2)
y_true = [1, 2, 3]
y_pred = [3, 2, 1]
r2 = sk_metrics.r2_score(y_true, y_pred)
print(r2)

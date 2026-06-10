"""
y, sklearn - hyperparameter validation_curve.py, 2019.10.12
[1] https://datascienceschool.net/view-notebook/ff4b5d491cc34f94aea04baca86fbef8/

Three hyper parameter optimization methods with scikit-learn
------------------------------------------------------------
1) Validation_curve
2) GridSearchCV
3) ParameterGrid
"""

from sklearn.datasets import load_digits
from sklearn.svm import SVC
from sklearn.model_selection import validation_curve
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

digits = load_digits()
X, y = digits.data, digits.target

param_range = np.logspace(-6, -1, 10)

train_scores, test_scores = validation_curve(SVC(), X, y, param_name="gamma", param_range=param_range,
                                             cv=10, scoring="accuracy", n_jobs=1)

train_scores_mean = np.mean(train_scores, axis=1)
train_scores_std = np.std(train_scores, axis=1)
test_scores_mean = np.mean(test_scores, axis=1)
test_scores_std = np.std(test_scores, axis=1)

mpl.rcParams["font.family"] = 'DejaVu Sans'
plt.semilogx(param_range, train_scores_mean, label="Training score", color="r")
plt.fill_between(param_range, train_scores_mean - train_scores_std,
                 train_scores_mean + train_scores_std, alpha=0.2, color="r")
plt.semilogx(param_range, test_scores_mean,
             label="Cross-validation score", color="g")
plt.fill_between(param_range, test_scores_mean - test_scores_std,
                 test_scores_mean + test_scores_std, alpha=0.2, color="g")
plt.legend(loc="best")
plt.title("Validation Curve with SVM")
plt.xlabel("$\gamma$")
plt.ylabel("Score")
plt.ylim(0.0, 1.1)
plt.show()



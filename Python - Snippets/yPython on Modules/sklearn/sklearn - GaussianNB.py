"""
y, 2020.8.15
https://datascienceschool.net/view-notebook/731e0d2ef52c41c686ba53dcaf346f32/
https://datascienceschool.net/view-notebook/c19b48e3c7b048668f2bb0a113bd25f7/
"""

from sklearn.naive_bayes import GaussianNB, BernoulliNB, MultinomialNB
from sklearn.datasets import load_iris
from sklearn.preprocessing import label_binarize
from sklearn.metrics import roc_curve, precision_score
import numpy as np
import matplotlib.pyplot as plt

iris = load_iris()
X = iris.data  # X.shape=(150,4)

y_true = iris.target  # iris.target.shape = y_true.shape = (150,)
model = GaussianNB().fit(X, y_true)
y_pred = model.predict(X)
y_pred = np.array([np.argmax(line) for line in y_pred])
print(f"\tprecision_score={precision_score(y_true, y_pred, average=None).mean():.4g}")

y_true = label_binarize(iris.target, [0, 1, 2])  # y_true.shape = (150,3), iris.target.shape = (150,)
fpr = [None] * 3
tpr = [None] * 3
thr = [None] * 3
lines = [None] * 3
for j in range(3):
    model = GaussianNB().fit(X, y_true[:, j])
    fpr[j], tpr[j], thr[j] = roc_curve(y_true[:, j], model.predict_proba(X)[:, 1])
    lines[j], = plt.plot(fpr[j], tpr[j])
plt.xlabel('Increasing false positive rates (fpr)')
plt.ylabel('Increasing true positive rates (tpr)')
plt.legend(handles=lines, labels=[f"class {j}" for j in range(3)], loc='lower right')
plt.show()



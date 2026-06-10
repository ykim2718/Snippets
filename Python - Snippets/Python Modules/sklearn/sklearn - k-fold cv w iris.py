"""
y, sklearn - k-fold cv w iris.py, 2018.11.26, 11.28
https://tensorflow.blog/tag/cross-validation/
https://github.com/rickiepark/introduction_to_ml_with_python/blob/master/RepeatedKFold.ipynb
"""

from sklearn.datasets import load_iris
from sklearn.model_selection import cross_val_score, KFold, StratifiedKFold
from sklearn.linear_model import LogisticRegression
import matplotlib.pyplot as plt

iris = load_iris()
# logreg = LogisticRegression(solver='liblinear', multi_class='auto', max_iter=1000)
logreg = LogisticRegression(solver='liblinear', multi_class='ovr', max_iter=1000)  # ovr ???

print('-' * 32, 'RepeatedKFold')

kfold = KFold(n_splits=5)
scores = cross_val_score(logreg, iris.data, iris.target, cv=kfold)
print(scores, scores.mean())

from sklearn.model_selection import RepeatedKFold
rkfold = RepeatedKFold(n_splits=5, n_repeats=5, random_state=42)
scores = cross_val_score(logreg, iris.data, iris.target, cv=rkfold)
print(scores, scores.mean())

plt.boxplot(scores)
plt.show()

print('-' * 32, 'StratifiedKFold')

skfold = StratifiedKFold(n_splits=5)
scores = cross_val_score(logreg, iris.data, iris.target, cv=skfold)
print(scores, scores.mean())

print('-' * 32, 'RepeatedStratifiedKFold')

from sklearn.model_selection import RepeatedStratifiedKFold
rskfold = RepeatedStratifiedKFold(n_splits=5, n_repeats=5, random_state=42)
scores = cross_val_score(logreg, iris.data, iris.target, cv=rskfold)
print(scores, scores.mean())

plt.boxplot(scores)
plt.show()


from sklearn.model_selection import GridSearchCV, train_test_split
X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, random_state=42)
param_grid = {'C': [0.001, 0.01, 0.1, 1, 10, 100, 1000]}
grid_search = GridSearchCV(logreg, param_grid, cv=rskfold, return_train_score=True, iid=False)
grid_search.fit(X_train, y_train)

print(grid_search.score(X_test, y_test), grid_search.best_params_, grid_search.best_score_)

for k in grid_search.cv_results_:
    if 'split' in k:
        print(k, grid_search.cv_results_[k])



"""
y, sklearn - hyperparameter GridSearchCv.py, 2019.10.12
[1] https://datascienceschool.net/view-notebook/ff4b5d491cc34f94aea04baca86fbef8/

Three hyper parameter optimization methods with scikit-learn
------------------------------------------------------------
1) Validation_curve
2) GridSearchCV
3) ParameterGrid
"""

from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC

pipe_svc = Pipeline([('scl', StandardScaler()), ('clf', SVC(random_state=1))])

param_range = [0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0, 1000.0]
param_grid = [
    {'clf__C': param_range, 'clf__kernel': ['linear']},
    {'clf__C': param_range, 'clf__gamma': param_range, 'clf__kernel': ['rbf']}]

gs = GridSearchCV(estimator=pipe_svc, param_grid=param_grid,
                  scoring='accuracy', cv=10, n_jobs=1)
gs = gs.fit(X, y)

print(gs.cv_results_["params"])
print(gs.cv_results_["mean_test_score"])

print(gs.best_score_)
print(gs.best_params_)

"""
y, sklearn - hyperparameter parameterGrid.py, 2019.10.12
[1] https://datascienceschool.net/view-notebook/ff4b5d491cc34f94aea04baca86fbef8/

Three hyper parameter optimization methods with scikit-learn
------------------------------------------------------------
1) Validation_curve
2) GridSearchCV
3) ParameterGrid
"""

from sklearn.model_selection import ParameterGrid


param_grid = {'a': [1, 2], 'b': [True, False]}
print(list(ParameterGrid(param_grid)))

param_grid = [{'kernel': ['linear']}, {'kernel': ['rbf'], 'gamma': [1, 10]}]
print(list(ParameterGrid(param_grid)))

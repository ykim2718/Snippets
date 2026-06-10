"""
y, sklearn - imputer.py, 2019.1.24
https://datascienceschool.net/view-notebook/3e7aadbf88ed4f0d87a76f9ddc925d69/
https://datascienceschool.net/view-notebook/f43be7d6515b48c0beb909826993c856/   Scikit-Learn의 문서 전처리 기능
"""

from sklearn.preprocessing import Imputer
import numpy as np

imp = Imputer(missing_values='NaN', strategy='mean', axis=0)
r = imp.fit_transform([[1, 2], [np.nan, 3], [7, 6], [99, np.nan]])
print(r, type(r))



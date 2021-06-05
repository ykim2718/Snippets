"""
y, 2020.9.19
numpy - cholesky basic 2.py
https://blogs.sas.com/content/iml/2012/02/08/use-the-cholesky-transformation-to-correlate-and-uncorrelate-variables.html
https://stackoverflow.com/questions/619335/a-simple-algorithm-for-generating-positive-semidefinite-matrices
https://en.wikipedia.org/wiki/Definite_symmetric_matrix#Negative-definite.2C_semidefinite_and_indefinite_matrices
"""

import numpy as np

a = np.arange(9)
np.random.shuffle(a)
a = a.reshape(3, 3)
print(f"random matrix=\n{a}")
a = np.dot(a, a.transpose())  # make positive semidefinite matrix for any mantrix
print(f"positive definite matrix=\n{a}")


def is_pos_def(x):
    return np.all(np.linalg.eigvals(x) > 0)


print(f"positive definite={is_pos_def(a)}")

L = np.linalg.cholesky(a)
print(f"cholesky matrix=\n{L}")

"""
y, 2023.6.1
numpy - linalg.solve.py
https://numpy.org/doc/stable/reference/generated/numpy.linalg.solve.html
    linalg.solve(a, b)
        Solve a linear matrix equation, or system of linear scalar equations.
        Computes the “exact” solution, x, of the well-determined, i.e., full rank, linear matrix equation ax = b.
        a must be square and of full-rank, i.e., all rows (or, equivalently, columns) must be linearly independent;
        if either is not true, use lstsq for the least-squares best “solution” of the system/equation.
"""

import numpy as np


'''
    x0 + 2 * x1 = 1
    3* x0 + 5 * x1 = 2
'''
a = np.array([[1, 2], [3, 5]])
b = np.array([1, 2])
x = np.linalg.solve(a, b)
print(f"{x=}")

c = np.allclose(np.dot(a, x), b)
print(f"{c=}")

'''
x=array([-1.,  1.])
c=True
-1 + 2 * 1 = 1
3 * -1 + 5 * 1 = 2
'''

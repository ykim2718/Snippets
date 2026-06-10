"""
y, 2023.6.1
numpy - linalg.lstsq.py
https://numpy.org/doc/stable/reference/generated/numpy.linalg.lstsq.html#numpy.linalg.lstsq
    linalg.lstsq(a, b, rcond='warn')
        Return the least-squares solution to a linear matrix equation.
        Computes the vector x that approximately solves the equation a @ x = b.
"""

import numpy as np
import matplotlib.pyplot as plt

x = np.array([0, 1, 2, 3])
y = np.array([-1, 0.2, 0.9, 2.1])

A = np.vstack([x, np.ones(len(x))]).T
print(f"{A=}")

m, c = np.linalg.lstsq(A, y, rcond=None)[0]
print(f"{m, c=}")

'''
A=array([[0., 1.],
       [1., 1.],
       [2., 1.],
       [3., 1.]])
m, c=(0.9999999999999997, -0.9499999999999992)
'''
y_hat = m * x + c

_ = plt.plot(x, y, 'o', label='Original data', markersize=10)
_ = plt.plot(x, y_hat, 'r', label='Fitted line')
_ = plt.legend()
plt.show()

"""
y, 2023.6.1
numpy - linalg.lstsq (2).py
https://numpy.org/doc/stable/reference/generated/numpy.linalg.lstsq.html#numpy.linalg.lstsq
    linalg.lstsq(a, b, rcond='warn')
        Return the least-squares solution to a linear matrix equation.
        Computes the vector x that approximately solves the equation a @ x = b.
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredText
from scipy import stats

x = np.array([
    [-1.41, -1.26, -0.69],
    [0.43, 1.04, -0.07],
    [-1.57, 0.18, 1.01],
    [-1.04, 0.44, 1.29],
    [2.61, -0.36, 1.04],
    [0.28, -0.89, 0.54],
    [0.00, -0.62, -0.45],
    [-1.56, 0.51, -1.17],
    [0.96, -0.62, -1.02],
    [0.65, -0.67, -0.36]
])
y = np.array([
    0.23, -0.47, -0.48, -0.22, 3.01, 1.66, 0.69, -1.88, 1.08, 1.24
])

ones = np.expand_dims(np.ones(x.shape[0]), axis=1)
solu, resi, rank, sing = np.linalg.lstsq(np.concatenate([x, ones], axis=1), y, rcond=None)
print(f"Least-squares solution={solu}")
print(f"Sum of squared residuals={resi}")
print(f"rank={rank}")
print(f"singular values of 'correlation matrix'={sing}")
y_hat = x * solu[:-1] + solu[-1]

fig = plt.figure()
fig.set_size_inches(8, 6)
fig.set_dpi(100)
ax1 = fig.add_subplot()
for j, (color, label) in enumerate(zip(['C0', 'C1', 'C2'], ['A', 'B', 'C'])):
    ax1.plot(x[:, j], y, 'o', color=color, label=label)
ax1.set_xlabel('A, B, C')
ax1.set_ylabel('y = f(A, B, C)')
text = ''
for j, (color, label) in enumerate(zip(['C0', 'C1', 'C2'], ['A', 'B', 'C'])):
    x_, y_ = x[:, j], y_hat[:, j]
    # FIXME !! need to sort x_ and y_
    slope, intercept, r_value, p_value, std_err = stats.linregress(x_, y_)
    text += f"[{label}] {slope=:.3g} {intercept=:.3g}\n"
    ax1.plot(x_, y_, color=color, label=label)
text = text.rstrip()
print(text)
at = AnchoredText(text, prop={}, frameon=False, loc='lower right')
ax1.add_artist(at)
ax1.legend()
plt.show()

"""
https://www.askpython.com/python-modules/numpy/numpy-linalg-lstsq
# assigning the arrays
# the coefficient matrix
A = np.array([[1, 2],
              [-1, 1],
              [0, 3]])
# the coordinate matrix
B = np.array([1, 3, 0])
# displaying the original matrices
print("The coefficient matrix is =", A)
print("the coordinate matrix is=", B)
# calculating the approximate values
R, residuals, RANK, sing = np.linalg.lstsq(A, B, rcond=None)
# displaying the results
print("the least square solutions are'", R)
print("the residuals are=", residuals)
print("The singular values of the coefficient matrix are=", sing)
print("the rank of the matrix is", RANK)
"""

"""
y, numpy - how to force zero intercept in linear regression.py, 2019.12.5
https://stackoverflow.com/questions/9990789/how-to-force-zero-interception-in-linear-regression
"""

import numpy as np
import matplotlib.pyplot as plt

x = np.array([0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0, 4.0, 6.0, 8.0, 10.0,
              20.0, 40.0, 60.0, 80.0])

y = np.array([0.50505332505407008, 1.1207373784533172, 2.1981844719020001,
              3.1746209003398689, 4.2905482471260044, 6.2816226678076958,
              11.073788414382639, 23.248479770546009, 32.120462301367183,
              44.036117671229206, 54.009003143831116, 102.7077685684846,
              185.72880217806673, 256.12183145545811, 301.97120103079675])

# y, 2019.12.5
x = np.array([1, 2, 3])
y = np.array([3, 2, 1])

# Our model is y = a * x, so things are quite simple, in this case...
# x needs to be a column vector instead of a 1D vector for this, however.
x = x[:, np.newaxis]
a, _, _, _ = np.linalg.lstsq(x, y)

# y, 2019.12.5
print(a)
slope = a[0]
y_pred = (a * x).flatten()
print(y_pred)

def compute_r2(y_true, y_pred):
    sse = sum((y_true - y_pred) ** 2)
    tse = (len(y_true) - 1) * np.var(y_true, ddof=1)
    r2 = 1 - (sse/tse)
    return r2, sse, tse


print(compute_r2(y, y_pred))  # (-2.4285714285714284, 6.857142857142857, 2.0) << same as excel

plt.plot(x, y, 'bo')
plt.plot(x, a * x, 'r-')
plt.show()

"""
y, sklearn - linear models.py, 2018.12.6
https://datascienceschool.net/view-notebook/83d5e4fff7d64cb2aecfd7e42e1ece5e/  << Blogger
"""

import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression, Ridge, Lasso
from sklearn.metrics import r2_score
import matplotlib.pyplot as plt

def print_model_eq(model):

    weight = np.append(model.coef_, model.intercept_)
    formula = str()
    for j in range(len(weight)-1):
        formula = formula + str("%g" % weight[j]) + str("x") + str(j+1) + str(" ")
        if weight[j+1] >= 0:
            formula = formula + str("+")
        formula = "y =" + formula + str("%.2f" % weight[-1])
        print("model eq:", formula)


def make_nonlinear_data(seed=0, n_samples=50):
    """ y, 2018.12.7 """

    X1 = np.sort(np.random.rand(n_samples))
    X2 = np.sort(np.random.rand(n_samples))
    y = np.sin(2 * np.pi * X1) + np.sin(2 * np.pi * X2) + np.random.randn(n_samples) * 0.1
    # X = X[:, np.newaxis]
    X = np.c_[X1, X2]  # c_ is indexer
    return (X, y)


model_names = ['LinearRegression', 'Ridge', 'Lasso']
colors = ['r', 'g', 'b']
alpha_value = 0.1

X, y = make_nonlinear_data()
train_x, test_x, train_y, test_y = train_test_split(X, y, test_size=0.33)
print('X and y shape =', X.shape, y.shape)
print('train shape =', train_x.shape, train_y.shape)
print('test shape =', test_x.shape, test_y.shape)

fig = plt.figure()
ax1 = fig.add_subplot(1, 1, 1)
ax1.scatter(X[:, 0], y, color='m', alpha=0.5)
ax1.scatter(X[:, 1], y, color='c', alpha=0.5)

for j, model_name in enumerate(model_names):

    print("{:-<66}".format(model_name))
    model = {
        'LinearRegression': LinearRegression(),
        'Ridge': Ridge(alpha=alpha_value),
        'Lasso': Lasso(alpha=alpha_value),
    }[model_name]

    model.fit(train_x, train_y)
    print_model_eq(model)

    train_perf = r2_score(train_y, model.predict(train_x))
    test_perf = r2_score(test_y, model.predict(test_x))
    print("performance: train=%.4f, test=%.4f" % (train_perf, test_perf))

    x = test_x[:, 0]
    y = model.predict(test_x)
    z = np.array(sorted(zip(x, y), key=lambda z: z[0]))
    x, y = z[:, 0], z[:, 1]
    del z
    ax1.plot(x, y, color=colors[j])

plt.show()

"""
y, 2021.12.13
statsmodels - OLS basic.py
https://www.statsmodels.org/dev/generated/statsmodels.regression.linear_model.OLS.html
"""

import statsmodels.api as sm
import numpy as np

if False:
    duncan_prestige = sm.datasets.get_rdataset("Duncan", "carData")
    Y = duncan_prestige.data['income']
    X = duncan_prestige.data['education']
    X = sm.add_constant(X)
else:
    X = np.array([1, 2, 3])
    Y = np.array([3, 2, 1])
    # Excel: (y=0.7143x, R2=-2.429) or (y=-x+4, R2=1)
    # X = sm.add_constant(X)
model = sm.OLS(Y, X)
results = model.fit()
print(results.summary())
print(results.params)
print(results.rsquared)
print(results.rsquared_adj)
# print(results.tvalues)
# print(results.t_test[0]))
# print(results.t_test[1]))

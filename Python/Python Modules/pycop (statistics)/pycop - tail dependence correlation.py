"""
y, 2024.9.16
pycop - tail dependence correlation.py
https://pypi.org/project/pycop/
https://www.perplexity.ai/search/how-to-avoid-conversionerror-f-mwoYJfUOQhCy4o2eMAn.3g?login-source=visitorGate
"""


import pycop
import numpy as np
import scipy.stats as ss
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


n = 3       # Dimension
m = 1000    # Sample size

corrMatrix = np.array([[1, 0.9, 0], [0.9, 1, 0], [0, 0, 1]])
u = pycop.simulation.simu_gaussian(n, m, corrMatrix)
u = ss.norm.ppf(u)

f = pd.DataFrame(u.T, columns=list('XYZ'))
print(f"{f.shape=}")

case = 2
if case == 0:
    pd.plotting.scatter_matrix(f, alpha=0.2)
elif case == 1:
    sns.pairplot(f, height=1.7)
elif case == 2:
    g = sns.pairplot(f, diag_kind='kde', height=1.7)
    g.map_upper(sns.kdeplot, levels=3, color='.2')
plt.show()


cop = pycop.empirical(f[['X', 'Y']].values)

ltdc = cop.LTDC(0.01)  # i/n = 1%
utdc = cop.UTDC(0.99)  # i/n = 99%
print(f"Lower Tail Dependence Coefficient: {ltdc=}")
print(f"Upper Tail Dependence Coefficient: {utdc=}")

optimal_ltdc = cop.optimal_tdc('lower')
optimal_utdc = cop.optimal_tdc('upper')
print(f"Optimal Lower TDC: {optimal_ltdc=}")
print(f"Optimal Upper TDC: {optimal_utdc=}")
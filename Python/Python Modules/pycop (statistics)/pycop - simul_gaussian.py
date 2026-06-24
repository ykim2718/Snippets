"""
y, 2024.8.15
pycop - simul_gaussian.py
https://github.com/maximenc/pycop/
https://github.com/maximenc/pycop/blob/master/examples/example_plot.ipynb
https://www.kaggle.com/code/muhammedtausif/scatterplot-matrix-with-seaborn   << Scatterplot Matrix with SEABORN
"""

import pandas as pd
import pycop
import numpy as np
import scipy.stats as ss
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

n = 3       # Dimension
m = 1000    # Sample size

corrMatrix = np.array([[1, 0.9, 0], [0.9, 1, 0], [0, 0, 1]])
u = pycop.simulation.simu_gaussian(n, m, corrMatrix)
u = ss.norm.ppf(u)

f = pd.DataFrame(u.T, columns=list('XYZ'))

case = 2
if case == 0:
    pd.plotting.scatter_matrix(f, alpha=0.2)
elif case == 1:
    sns.pairplot(f, height=1.7)
elif case == 2:
    g = sns.pairplot(f, diag_kind='kde', height=1.7)
    g.map_upper(sns.kdeplot, levels=3, color='.2')
plt.show()
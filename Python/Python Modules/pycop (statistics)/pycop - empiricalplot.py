"""
y, 2024.9.16
pycop - empiricalplot.py
https://pypi.org/project/pycop/
https://github.com/maximenc/pycop/blob/master/examples/example_simu.ipynb
"""


from pycop import utils, simulation
import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt


n = 3
m = 1000

# We defined the correlation matrix:
corrMatrix = np.array([[1, 0.9, 0], [0.9, 1, 0], [0, 0, 1]])
u = simulation.simu_gaussian(n, m, corrMatrix)
u = norm.ppf(u)
utils.empiricalplot(u, contour=True)
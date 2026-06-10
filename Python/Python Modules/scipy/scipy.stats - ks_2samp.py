"""
y, 2020.11.1 - 2
scipy.stats - ks2_2samp.py
https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.ks_2samp.html#scipy.stats.ks_2samp
"""

import scipy.stats as sc_stats
import numpy as np

expected = np.array([1, 2, 3, 4])
# observed = expected                  # KstestResult(statistic=0.0, pvalue=1.0)
# observed = np.array([2, 3, 4, 5])    # KstestResult(statistic=0.25, pvalue=1.0)
# observed = np.array([2, 4, 6, 8])    # KstestResult(statistic=0.5, pvalue=0.7714285714285716)
# observed = np.array([3, 6, 9, 12])   # KstestResult(statistic=0.75, pvalue=0.22857142857142862)
# observed = np.array([4, 8, 12, 16])  # KstestResult(statistic=0.75, pvalue=0.22857142857142862)
# observed = np.array([10, 20, 30, 40])  # KstestResult(statistic=1.0, pvalue=0.028571428571428577)
observed = np.array([4, 3, 2, 1])   # KstestResult(statistic=0.0, pvalue=1.0)  <<<< ????

result = sc_stats.ks_2samp(observed, expected)
print(result)

"""
y, scipy.stats - spearman correlation.py, 2019.1.18
https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.spearmanr.html
"""

import scipy.stats as ss

sr = ss.spearmanr([1, 2, 3], [4, 5, 6], axis=0)  # default: axis=0
print(sr)
print(sr.correlation)
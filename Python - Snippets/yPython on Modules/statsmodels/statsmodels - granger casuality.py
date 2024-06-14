"""
y, 2021.3.16
statsmodels - granger casuality.py
https://en.wikipedia.org/wiki/Granger_causality
https://www.statsmodels.org/stable/generated/statsmodels.tsa.stattools.grangercausalitytests.html
    .. The null hypothesis for all four test is that the coefficients corresponding to past values of the second
       time series are zero.
https://www.youtube.com/watch?v=b8hzDzGWyGM
https://www.youtube.com/watch?v=4TkNZviNJC0  ★
"""

import statsmodels.api as sm
from statsmodels.tsa.stattools import grangercausalitytests
import numpy as np

data = sm.datasets.macrodata.load_pandas()
frame = data.data[["realgdp", "realcons"]].pct_change(fill_method=None).dropna()
print(frame.shape)

gc_res = grangercausalitytests(frame, 4, verbose=True)  # all lags up to 4
# print(gc_res)
# print(type(gc_res))
# print(gc_res.keys())
print(gc_res[4])

"""
y, talib - rolling mean.py, 2018.7.21, 7.22 (Monpetit)
https://stackoverflow.com/questions/13728392/moving-average-or-running-mean/27681394
https://pypi.org/project/TA-Lib/#files
pip install talib  >> no working
pip install ta-lib  >> failed in finding c header file: _ta_libc.h
https://www.lfd.uci.edu/~gohlke/pythonlibs/#ta-lib  >>> working
    Unofficial Windows Binaries for Python Extension Packages
"""

import talib as ta
import numpy as np
import pandas as pd
import scipy
from scipy import signal


period = 30
array = np.random.randint(0, 99, 33)
print('array:', array)


def cumsum_sma(array, period):
    ret = np.cumsum(array, dtype=float)
    ret[period:] = ret[period:] - ret[:-period]
    return ret[period - 1:] / period

def pandas_sma(array, period):
    # return pd.rolling_mean(array, period)
    return pd.Series(array).rolling(window=period).mean()

def api_sma(array, period):
    # this method is native to Tradewave and does NOT return an array
    return (data[PAIR].ma(PERIOD))

def talib_sma(array, period):
    return ta.MA(np.array(array).astype(float), period)

def convolve_sma(array, period):
    return np.convolve(array, np.ones((period,))/period, mode='valid')

def fftconvolve_sma(array, period):
    return scipy.signal.fftconvolve(array, np.ones((period,))/period, mode='valid')

import timeit

stmt = "cumsum_sma(array, period)"
print(stmt + ':', timeit.timeit(setup="import numpy as np", stmt=stmt, globals=globals(), number=10000))
stmt = "pandas_sma(array, period)"
print(stmt + ':', timeit.timeit(setup="import pandas as pd", stmt=stmt, globals=globals(), number=10000))
stmt = "talib_sma(array, period)"
print(stmt + ':', timeit.timeit(setup="import talib as ta", stmt=stmt, globals=globals(), number=10000))
stmt = "convolve_sma(array, period)"
print(stmt + ':', timeit.timeit(setup="import numpy as np", stmt=stmt, globals=globals(), number=10000))
stmt = "fftconvolve_sma(array, period)"
print(stmt + ':', timeit.timeit(setup="from scipy import signal", stmt=stmt, globals=globals(), number=10000))

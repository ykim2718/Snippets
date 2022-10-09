"""
y, 2022.10.9
npext- rolling two columns.py
https://pypi.org/project/numpy-ext/
"""

import pandas as pd
import numpy_ext as npext  #  pip install numpy-ext

df = pd.DataFrame(dict(a=[1, 2, 3, 4], b=[5, 6, 8, 9]))
# print(df)


def my_func(a, b, param=1):
    return (a.sum() + b.sum()) / param


a = npext.rolling_apply(my_func, 2, df.a.values, df.b.values, param=10)
print(a)
"""
[nan 1.4 1.9 2.4]
"""

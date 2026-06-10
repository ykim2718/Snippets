"""
y, pandas series - map with dict mapping.py, 2018.9.29
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.Series.map.html
"""

import pandas as pd
import numpy as np


def print_it(expr):

    print('\n', expr, '=\n', eval(expr))


x = pd.Series([1, 2, 3], index=['one', 'two', 'three'])
y = pd.Series(['foo', 'bar', 'baz'], index=[1, 2, 3])
print_it('x')
print_it('y')
print_it('x.map(y)')

z = {1: 'A', 2: 'B', 3: 'C'}
print_it('z')
print_it('x.map(z)')

s = pd.Series([1, 2, 3, np.nan])
print_it('s')
print_it("s.map('this is a string {}'.format, na_action=None)")
print_it("s.map('this is a string {}'.format, na_action='ignore')")

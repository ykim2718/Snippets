"""
y, pandas - apply to values in series.py, 2018.7.29 - 30
"""

import pandas as pd
import sklearn.preprocessing as sk_pp
import numpy as np

a = pd.Series([-2, -1, 0, 1, 2], index=list('abcde'))
a = pd.Series([None, -1, 0, 1, None], index=list('abcde'))
# a.index = list('abcdd')


def yDsApply(series, function, ignore_nan_outside=True):
    """ y, 2018.7.29 - 30 """

    assert isinstance(series, pd.Series)

    if ignore_nan_outside and series.hasnans:
        assert series.index.is_unique, "need unique index to ignore nan outside but found duplicated"
        first_valid_index, last_valid_index = series.first_valid_index(), series.last_valid_index()
        assert not series[first_valid_index:last_valid_index].hasnans, "allow nan outside but found inside"
        valid_mask = pd.Series(True, index=series.index)
        valid_mask[:first_valid_index] = False
        valid_mask[last_valid_index:] = False
        valid_mask[first_valid_index] = True
        valid_mask[last_valid_index] = True
        series = series.copy()
        series[valid_mask] = function(series[valid_mask].astype(float))
        series[~valid_mask] = np.nan
        return series.values
    else:
        return function(series.astype(float))


print('sk_pp.scale(x):', yDsApply(a, sk_pp.scale))
# print('sk_pp.robust_scale(x):', yDsApply(a, sk_pp.robust_scale))
print('sk_pp.minmax_scale(x):', yDsApply(a, sk_pp.minmax_scale))
print('sk_pp.maxabs_scale(x):', yDsApply(a, sk_pp.maxabs_scale))


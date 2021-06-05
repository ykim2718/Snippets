"""
y, Pandas - set and reset multi-index.py, 2017.7.24
"""

import pandas as pd
df = pd.DataFrame([[0, 1, 2], [3, 4, 5], [0, 7, 8]], columns=list('abc'), index=list('xyz'))
print(df)


def yDfSetMultiIndex(df, col_names, **kwargs):
    """ y, 2017.6.7, 7.24 """

    if df.index.names != col_names:
        assert set(df.columns) >= set(col_names)
        df = df.reset_index(**kwargs)
        df = df.sort_values(by=col_names, axis=0)
        df = df.set_index(col_names)

    return df


def yDfResetMultiIndex(df, col_name=None, **kwargs):
    """ y, 2017.6.7, 7.24 """

    df = df.reset_index(**kwargs)
    if bool(col_name):
        assert col_name in df.columns
        df = df.set_index(col_name)

    return df

df = yDfSetMultiIndex(df, list('ab'), drop=True)
print(df)
df = yDfResetMultiIndex(df, 'c')
print(df)

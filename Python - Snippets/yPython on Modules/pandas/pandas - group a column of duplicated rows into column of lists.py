"""
y, pandas - group a column of duplicated rows into column of lists.py, 2018.9.30
https://stackoverflow.com/questions/45489571/pandas-group-columns-of-duplicate-rows-into-column-of-lists
"""

import pandas as pd
import numpy as np


def yDfSqueezeValueColumnByValueList(frame, key_columns, value_column,
                                            new_column=None, keep_other_columns=False):
    """
    y,  2018.9.30

    Reference
    ---------
    https://stackoverflow.com/questions/45489571/pandas-group-columns-of-duplicate-rows-into-column-of-lists

    Usage
    -----
    >> df = pd.DataFrame({'key': [1, 1, 1, 2, 2, 3, 3], 'value': [1, 2, 3, 4, 5, 6, 6]})
    >> print(yDfSqueezeValueColumnByValueList(df, ['key'], 'value', 'values'))
           key     values
        0    1  [1, 2, 3]
        1    2     [4, 5]
        2    3     [6, 6]

    """

    assert isinstance(key_columns, list)
    assert all([key_column in frame.columns for key_column in key_columns])
    assert isinstance(value_column, str) and value_column in frame.columns
    assert isinstance(new_column, (str, type(None)))
    if new_column:
        assert new_column not in frame.columns
    else:
        new_column = value_column
    assert keep_other_columns in [False, 'first', 'last']

    f1 = frame.groupby(key_columns)[value_column].apply(list).reset_index(name=new_column)
    if keep_other_columns:
        other_columns = set(frame.columns) - set(key_columns + [new_column])
        f2 = frame.groupby(key_columns).agg({k: keep_other_columns for k in other_columns}).reset_index()
        frame = f1.merge(f2, on=key_columns, how='left')
    else:
        frame = f1
    return frame


df = pd.DataFrame({'key': [1, 1, 1, 2, 2, 3, 3], 'value': [1, 2, 3, 4, 5, 6, 6], 'other': list('abcdefg')})
print(df)

if False:
    r = df.groupby('key')['value'].apply(list).reset_index(name='values')
else:
    # r = yDfSqueezeValueColumnByValueList(df, ['key'], 'value', 'values')
    r = yDfSqueezeValueColumnByValueList(df, ['key'], 'value')
print(r)
print(type(r.loc[0, 'value']))


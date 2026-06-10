"""
y, pandas - multilevel columns from a column.py, 2019.7.11
"""

import pandas as pd

df = pd.DataFrame({"foo": ['one', 'one', 'two', 'two'],
                   "bar": ['A', 'A', 'B', 'C'],
                   "baz": [1, 2, 3, 4]})
print(df)


def yDfSetMultilevelColumnsFromAColumn(frame, a_column):
    """ y, 2019.7.11 """

    assert isinstance(frame, pd.DataFrame)
    assert a_column in frame

    frame_new = pd.DataFrame()
    keys = frame[a_column].unique()
    for key in keys:
        mask = frame[a_column] == key
        df = frame[mask].drop([a_column], axis='columns')
        df.columns = pd.MultiIndex.from_product([[key], df.columns])
        frame_new = pd.concat([frame_new, df])

    return frame_new

df_new = yDfSetMultilevelColumnsFromAColumn(df, 'foo')
print(df_new)
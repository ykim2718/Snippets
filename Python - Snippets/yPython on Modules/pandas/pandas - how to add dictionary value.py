"""
y, 2021.1.6
pandas - how to add dictionary value.py
"""

import pandas as pd


a = pd.DataFrame()

try:
    a.loc[1, 1] = dict(a=0)
except ValueError as ex:
    print(ex)

a.loc[1, 1] = [dict(a=1)]
a.loc[2, 1] = [dict(a=2)]
print(a)

print('- ' * 16)


def yDfSetDictValue(frame, index, column, value):
    """ y, 2021.1.7 """

    assert isinstance(frame, pd.DataFrame)
    assert isinstance(value, dict)

    a = pd.Series([value], index=[index])
    frame = frame.reindex(frame.index.union(a.index))
    if column in frame:
        frame[column] = a.combine_first(frame[column])
    else:
        frame[column] = a
    return frame


a = pd.DataFrame([0, 1], columns=[0], index=[0, 1])
a = yDfSetDictValue(a, 1, 0, dict(a=1))
a = yDfSetDictValue(a, 0, 1, dict(a=2))
print(a)

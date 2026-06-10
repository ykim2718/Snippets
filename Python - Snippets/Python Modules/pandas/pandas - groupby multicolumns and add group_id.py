"""
y, 2020.11
pandas - groupby multicolumns and add group_id.py
"""

import pandas as pd


def yDfAddDuplicateGropuId(frame, columns, new_column='gid'):
    """ y, 2020.10.27 """

    assert isinstance(frame, pd.DataFrame)
    assert all(pd.Index(columns).isin(frame.columns))
    assert new_column not in frame.columns

    frame[new_column] = None
    gr = frame.groupby(columns)
    for j, (key, value) in enumerate(gr.groups.items()):
        frame.loc[value, new_column] = j
    return frame


frame = pd.DataFrame(dict(A=list('abbde'), B=list('bccef'), C=list('cdefg')))
print(frame)

frame = yDfAddDuplicateGropuId(frame, list('AB'))
print(frame)


"""
   A  B  C
0  a  b  c
1  b  c  d
2  b  c  e
3  d  e  f
4  e  f  g
   A  B  C  gid
0  a  b  c  0.0
1  b  c  d  1.0
2  b  c  e  1.0
3  d  e  f  2.0
4  e  f  g  3.0
"""
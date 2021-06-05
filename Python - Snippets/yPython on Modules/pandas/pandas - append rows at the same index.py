"""
y, pandas - append rows at the same index.py, 2018.4.7
"""


import pandas as pd
import numpy as np


def yDfReplacedRowsAtTheSameIndices(frame, with_frame, copy_null=True, append_new=False, inplace=True):
    """ y, 2018.4.7 """

    assert isinstance(frame, pd.DataFrame)
    assert isinstance(with_frame, pd.DataFrame)

    if inplace is False:
        frame = frame.copy(True)

    if not set(frame.columns).issuperset(set(with_frame.columns)):
        new_columns = set(with_frame.columns) - set(frame.columns)
        for new_column in new_columns:
            frame[new_column] = np.nan

    if append_new is False:
        new_indices = set(with_frame.index) - set(frame.index)
        with_frame = with_frame.drop(new_indices, axis=0)

    for index in with_frame.index:
        if copy_null is True:
            frame.loc[index, with_frame.columns] = with_frame.loc[index]
        else:
            mask = with_frame.loc[index].notna()
            frame.loc[index, with_frame.columns[mask]] = with_frame.loc[index][mask]

    return frame


df1 = pd.DataFrame({'a': [1, 2], 'b': [3, 4]}, index=list('AB'))
df1.index.name = 'df1'
df2 = pd.DataFrame({'a': [1, 2], 'b': [None, 4], 'c': [5, 6]}, index=list('BC'))
df2.index.name = 'df2'
print(df1)
print(df2)

df = df1.append(df2)
df.index.name = 'df1.append(df2)'
print(df)

df = yDfReplacedRowsAtTheSameIndices(df1, df2)
df.index.name = 'yDfReplacedRowsAtTheSameIndices(df1, df2, copy_null=False)'
print(df)

"""
     a  b
df1      
A    1  3
B    2  4
     a    b  c
df2           
B    1  NaN  5
C    2  4.0  6
                 a    b    c
df1.append(df2)             
A                1  3.0  NaN
B                2  4.0  NaN
B                1  NaN  5.0
C                2  4.0  6.0
                                                      a    b    c
yDfReplacedRowsAtTheSameIndices(df1, df2, copy_...               
A                                                   1.0  3.0  NaN
B                                                   1.0  NaN  5.0
"""

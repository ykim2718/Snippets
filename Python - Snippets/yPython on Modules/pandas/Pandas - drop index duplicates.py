"""
y, 2016.7.10 - 7.19, Pandas - drop index duplicates.py
"""
import pandas as pd

dx = pd.DataFrame({
    'A': ['foo', 'foo', 'foo', 'bar'],
    'B': [2, 1, 1, 1],
    'C': ['A', 'A', 'B', 'A']},
    index=[0, 1, 1, 2])


def drop_index_duplicates_in_place(df):
    _name = df.index.name
    df.reset_index(inplace=True)
    df.drop_duplicates(subset='index', keep='last', inplace=True)
    if _name is not None: df.set_index(_name, inplace=True)
    return df


def drop_index_duplicates_out_of_place(df):
    return df[~df.index.duplicated(keep=False)]


df = dx.copy(deep=True)
print('y, 2016.7.10, before in-place editing, %s\n' % id(df), df)
drop_index_duplicates_in_place(df)
print('after %s\n' % id(df), df)

df = dx.copy(deep=True)
print('y, 2016.7.19, before out-of-plce editing, %s\n' % id(df), df)
df = drop_index_duplicates_out_of_place(df)
print('after %s\n' % id(df), df)

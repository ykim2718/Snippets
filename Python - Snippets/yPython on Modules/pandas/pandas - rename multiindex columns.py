"""
y, 2022.6.27
pandas - rename multiindex columns.py
https://pandas.pydata.org/docs/reference/api/pandas.MultiIndex.set_levels.html
"""

import pandas as pd

a = pd.DataFrame([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
a.columns = pd.MultiIndex.from_tuples((("a", "b"), ("a", "c"), ("b", "d")))
print(a)


def rename_multiindex_columns(frame, mapper):
    n_levels = frame.columns.nlevels
    assert all([len(k) == n_levels for k in mapper.keys()])
    columns = []
    for j in range(n_levels):
        columns.append(frame.columns.get_level_values(j).to_list())
    for key, value, in mapper.items():
        for j, k in enumerate(key):
            if k in columns[j]:
                loc = columns[j].index(k)
                columns[j][loc] = value[j]
    frame.columns = pd.MultiIndex.from_arrays(columns, names=frame.columns.names)
    return frame


a = rename_multiindex_columns(a, {('b', 'd'): ('B', 'D')})
print(a)

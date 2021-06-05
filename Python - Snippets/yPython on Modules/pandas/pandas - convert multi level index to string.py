"""
y, pandas - convert multi level index to string.py, 2019.1.21
https://stackoverflow.com/questions/34417970/pandas-convert-index-type-in-multiindex-dataframe
"""

import pandas as pd

index = pd.MultiIndex.from_tuples([(10, 1), (10, 2), (20, 1)], names=list('AB'))
print(index)

try:
    index = index.astype(str)
except Exception as ex:
    CRED = '\033[91m'
    CEND = '\033[0m'
    print(CRED + str(ex) + CEND)


def convert_index_to_string(index):
    """ y, 2019.1.21 """

    assert isinstance(index, pd.Index)

    if index.nlevels == 1:
        index = index.astype(str)
    else:
        index = index.set_levels([level.astype(str) for level in index.levels])
    return index


index = convert_index_to_string(index)
print(index)

index = pd.Index([0, 1, 2])
print(index)
index = convert_index_to_string(index)
print(index)


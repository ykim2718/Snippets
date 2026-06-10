"""
y, 2023.12.1
pandas - non-overlapping rolling.py
https://stackoverflow.com/questions/57595661/non-overlapping-rolling-windows-in-pandas-dataframes
    >> df.groupby(df.index // n).min()
"""

import pandas as pd
import typing


index = pd.bdate_range('2023-1-1', '2023-1-10')
s = pd.Series(data=range(index.size), index=index, name='series')
print(f"{s=}")
f = pd.DataFrame(data=list(range(index.size)), index=index, columns=['frame'])
print(f"{f=}")


def non_overlapping_rolling(a, window, func) -> typing.Union[pd.Series, pd.DataFrame]:
    """
    y, 2023.12.1
    """

    assert isinstance(a, (pd.Series, pd.DataFrame))
    assert isinstance(window, int) and window >= 1
    assert callable(func)

    def _rolling(a=a, window=window):
        for j in range(0, len(a), window):
            yield a[j: j + window]

    d = dict()
    for a in _rolling():
        index, value = func(a)
        d |= {index: value}
    if pd.api.types.is_scalar(value):
        a = pd.Series(d)
    else:
        a = pd.DataFrame.from_dict(d, orient='index')
    return a


def my_func(a) -> tuple:
    index = a.index[-1]
    value = a.sum()
    return index, value


a = non_overlapping_rolling(s, 5, my_func)
print(f"{a=}")
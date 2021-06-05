"""
y, pandas - squeeze duplicated index filling missing values.py, 2019.1.22
"""

import pandas as pd
import numpy as np

frame = pd.DataFrame({'A': [1, 2, np.nan, np.nan, np.inf],
                      'B': [3, np.nan, np.nan, 5, np.nan],
                      'C': [np.nan, np.nan, 4, np.nan, 6]},
                     index=[0, 1, 0, 1, 1])
print(frame)

pd.options.mode.use_inf_as_na = True
# https://pandas.pydata.org/pandas-docs/stable/options.html

keep = 'last'
if frame.index.has_duplicates:
    dropped = pd.Series(False, index=frame.index)
    mask = frame.index.duplicated(keep=False)  # show all
    for index in frame.index[mask].unique():
        locs, = np.where(np.array(frame.index) == index)
        df = frame.loc[index]
        na_count = df.isna().sum()  # na = not available, such as None or np.nan
        if na_count[0] >= 1 and all(na_count == na_count[0]):  # equal na count
            av_count = len(df) - na_count  # av = available
            if all(av_count == 1):  # one av count
                ds = df.fillna(method='backfill').iloc[0]
                if keep == 'first':
                    frame.iloc[locs[0]] = ds.values
                    dropped.iloc[locs[1:]] = True
                elif keep == 'last':
                    frame.iloc[locs[-1]] = ds.values
                    dropped.iloc[locs[:-1]] = True
    frame = frame[~dropped]
print(frame)

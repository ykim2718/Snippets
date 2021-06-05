"""
y, PandasCreatDataFrame.py, 2016.5.17
"""

import pandas as pd
import datetime as dt

data = [[20160429, 1500, 41700, 41700, 41700, 41700, 7116],
        [20160429, 1450, 41800, 41850, 41800, 41800, 387],
        [20160429, 1449, 41850, 41850, 41800, 41800, 533],
        [20160429, 1448, 41800, 41850, 41750, 41850, 970]]

columns = ['date+', 'o', 'h', 'l', 'c', 'v']
df = pd.DataFrame(columns=columns)
for r in range(len(data)):
    yyyymmdd = str(data[r][0])
    hhmm = str(data[r][1])
    date = dt.datetime(int(yyyymmdd[0:4]), int(yyyymmdd[4:6]), int(yyyymmdd[6:8]),
                       int(hhmm[0:2]), int(hhmm[2:4]))
    data[r][0] = date
    data[r].pop(1)  # pop out 2nd column of hhmm

    # out-of-place editing
    print('out-of-place, before=', id(df))
    df = df.append(pd.Series(data[r], index=columns), ignore_index=True)
    print('out-of-place, after=', id(df))

    # in-place editing
    print('in-place, before=', id(df))
    df.iloc[-1] = data[r]
    print('in-place, after=', id(df))

df.set_index('date+', inplace=True)

print(df)

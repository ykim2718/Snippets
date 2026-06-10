"""
y, pandas - datetime index 2.py, 2017.10.25
"""

import pandas as pd


dt_index = pd.DatetimeIndex(start='2017-1-1', end='2017-1-31', freq='3D')
ds = pd.Series(list(range(len(dt_index))), index=dt_index)
print(ds)


def yDiGetDateToClosest(a_date, dt_index, where='exact'):
    """ y, 2017.10.25 """

    assert isinstance(dt_index, pd.DatetimeIndex), "unexpected type, {}".fomrat(type(dt_index))
    assert where in ['exact', 'close', 'earlier', 'later']

    if where == 'exact':
        return a_date if a_date in dt_index else None
    elif where == 'close':
        return min(dt_index, key=lambda x: abs((x - a_date).days))
    elif where == 'earlier':
        dt = dt_index[dt_index < a_date]
        return yDiGetDateToClosest(dt, a_date, where='close')
    elif where == 'later':
        dt = dt_index[dt_index > a_date]
        return yDiGetDateToClosest(dt, a_date, where='close')


a_date = pd.Timestamp('2017-1-23')
print(yDiGetDateToClosest(a_date, ds.index))
print(yDiGetDateToClosest(a_date, ds.index, where='exact'))
print(yDiGetDateToClosest(a_date, ds.index, where='close'))
print(yDiGetDateToClosest(a_date, ds.index, where='earlier'))
print(yDiGetDateToClosest(a_date, ds.index, where='later'))

# print(ds[a_date])



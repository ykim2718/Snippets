"""
y, PandasDatetimeIndex.py, 2016.5.20
"""

import pandas as pd
import datetime as dt

"""
# http://pandas.pydata.org/pandas-docs/stable/timeseries.html
# http://pandas.pydata.org/pandas-docs/stable/cookbook.html
df = pd.DataFrame({'year': [2015, 2016],
   ....:                    'month': [2, 3],
   ....:                    'day': [4, 5],
   ....:                    'hour': [2, 3]})
pd.to_datetime(df[['year', 'month', 'day']])
"""

# convert series to pandas.tslib.Timestamp

date_uk = pd.to_datetime(pd.Series(['05/23/2005']), format='%m/%d/%Y')
print(date_uk[0], type(date_uk[0]))
if isinstance(date_uk[0], dt.datetime):
    print('pandas.tslib.Timestamp is checked the same as datetime.datetime, very weird !!!')
    if type(date_uk[0]) is not dt.datetime:
        print('\t type check is working though: %s vs %s' % (type(date_uk[0]), dt.datetime))

# convert date string to TImestamp and datetime

date_uk = pd.to_datetime('05/23/2005', format='%m/%d/%Y')  # pandas.tslib.Timestamp
print(date_uk, type(date_uk))
date_uk = date_uk.to_pydatetime()  # datetime.datetime
print(date_uk, type(date_uk))
date_uk = date_uk.date()  # datetime.date
print(date_uk, type(date_uk))

# compare datetime.date

date_dt = dt.date(2016, 5, 20)
print(date_dt, type(date_dt))
print(max(date_dt, date_uk))

# special to cybos data

date_ts = pd.to_datetime('20160520 023456', format='%Y%m%d %H%M%S')  # pandas.tslib.Timestamp
print(date_ts, type(date_ts))
date_dt = date_ts.to_datetime()  # datetime.datetime
print(date_dt, type(date_dt))

# special to cybos data series

ymd = [20160518, 20160519, 20160520]
hms = [123456, 12345, 1234]
date_df = pd.DataFrame([ymd, hms]).T
date_df.columns = ['ymd', 'hms']
print(date_df)

method = 1

if method == 1:
    date_df['datetime'] = date_df.apply(
        lambda row: str(row['ymd']) + ' ' + '{:06}'.format(row['hms']), axis=1)
elif method == 2:
    def my_row_func(row):
        return str(row['ymd']) + ' ' + '{:06}'.format(row['hms'])


    date_df['datetime'] = date_df.apply(my_row_func, axis=1)

print(date_df)

date_df['datetime+'] = pd.to_datetime(date_df['datetime'], format='%Y%m%d %H%M%S')
print(date_df)

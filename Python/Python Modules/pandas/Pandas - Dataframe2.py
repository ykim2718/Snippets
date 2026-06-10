"""
Y. Kim, 2016.4.22
Concat, Append, Delete Row/Column
"""

import pandas as pd
import datetime as dt

print('\ny, 2016.4.23')
df = pd.DataFrame(
    [[1, 2], [3, 4], [5, 6], [7, 8]],
    index=[dt.datetime(2016, 1, 1),
           dt.datetime(2016, 1, 3),
           dt.datetime(2016, 1, 5),
           dt.datetime(2016, 1, 6)])
file = __file__[:-3] + 'a.csv'
df.to_csv(file, encoding='utf-8')  # date_format = %Y%m%d
df_old = pd.read_csv(file)
print('df_old\n', df_old)
df_new = df_old.append(df, ignore_index=False)
df_new[df_new.index.name] = df_new.index
df_new[df_new.index.name] = df_new[df_new.index.name].apply(lambda x: x.strftime('%Y-%m-%d'))
df_new.drop_duplicates(subset=df_new.index.name, keep='last', inplace=True)
df_new.set_index(df_new.index.name, inplace=True)
# df_new = df_new.groupby(level=0).last() # working
# df_new = df_new.groupby(df_new.index).first() # working
print('df_new\n', df_new)
file = __file__[:-3] + 'b.csv'
df_new.to_csv(file, encoding='utf-8')


def ConcatPandasDataFrameColumns(df_ref, df_add):
    # y, 2016.4.24
    # no in-place operation

    df_index_name_copy = df_ref.index.name
    df_index_name = 'df_index_name for ConcatPandasDataFrameColumns()'
    df_ref[df_index_name] = df_ref.index
    df_ref.reset_index(drop=True, inplace=True)
    df_new = pd.concat([df_ref, df_add], axis=1, join='outer')  # not in-place operation
    df_ref.set_index(df_index_name, inplace=True)
    df_ref.index.name = df_index_name_copy
    df_new.set_index(df_index_name, inplace=True)
    df_new.index.name = df_index_name_copy

    return df_new


def GetDataframeSliceBetweenDates(df, start, end):  # indices
    # y, 2016-4-24
    import time
    import datetime as dt

    format = "%Y-%m-%d"
    t = time.strptime(start, format)
    start = dt.date(t.tm_year, t.tm_mon, t.tm_mday)
    t = time.strptime(end, format)
    end = dt.date(t.tm_year, t.tm_mon, t.tm_mday)

    start = df.index.searchsorted(start)
    end = df.index.searchsorted(end)

    df_slice = df.ix[start:end]

    return df_slice


if __name__ == "__main__":
    import pandas as pd
    import datetime as dt

    print('\ny, 2016.4.24, concate dataframe columns w/o in-place op')
    df = pd.DataFrame({'col#1': ['a', 'b'], 'col#2': ['c', 'd']}, index=['1st', '2nd'])
    df_add = pd.DataFrame({'add': [1, 2, 3]})
    df_new = ConcatPandasDataFrameColumns(df, df_add)
    print('df_old\n', df)
    print('df_new\n', df_new)

    print('\ny, 2016.4.24, dataframe slicing by date conditions')
    df = pd.DataFrame(
        [[1, 2], [3, 4], [5, 6], [7, 8]],
        index=[dt.datetime(2016, 1, 1),
               dt.datetime(2016, 1, 3),
               dt.datetime(2016, 1, 5),
               dt.datetime(2016, 1, 6)])
    df = GetDataframeSliceBetweenDates(df, '2016-1-2', '2016-1-7')
    print(df)

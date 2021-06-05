"""
y, Pandas - groupby taking last.py, 2016.5.30, 7.27
"""

import pandas as pd


def get_dataframe_by_grouping_sorting_taking(
        df, groupby_list=[], col_sort_by=[], keep='last'):

    gr = df.groupby(groupby_list)
    for k, v in gr.groups.items():
        if len(v) > 1:
            dg = df.ix[v, :].sort_values(
                by=col_sort_by,
                ascending=False if keep.lower() == 'last' else True
            )
            df.drop(dg.index[1:], axis=0, inplace=True)
    return df


if __name__ == '__main__':
    df = pd.DataFrame({'A': ['foo', 'foo', 'foo', 'bar'],
                       'B': [2, 1, 1, 1],
                       'C': ['A', 'A', 'B', 'A']})
    print('before=\n', df)
    df = get_dataframe_by_grouping_sorting_taking(
        df, ['A', 'C'], 'B', 'last'
    )
    print('after=\n', df)

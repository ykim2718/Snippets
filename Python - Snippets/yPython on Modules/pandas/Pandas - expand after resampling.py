"""
y, Pandas - expand after resampling.py, 2017.2.18 - 19
"""

import pandas as pd
import numpy as np

rng = pd.date_range('1/1/2017', periods=10, freq='B')
df = pd.DataFrame({'a': np.random.randn(len(rng)), 'b': np.random.randn(len(rng)),}, index=rng)
print(df)
dr = df.resample('W').mean()
print(dr)

def get_label_indices_by_period_id(pd_index, by_year, by_month=None, by_week=None):
    """ y, 2017.2.19 """

    assert isinstance(pd_index, pd.Index)
    assert isinstance(by_year, (type(None), int))
    assert isinstance(by_month, (type(None), int))
    assert isinstance(by_week, (type(None), int))
    assert type(by_month) != type(by_week)

    m_year = pd_index.year == by_year
    m_month = pd_index.month == by_month if by_month else True
    m_week = pd_index.week == by_week if by_week else True
    ds = pd_index[m_year & m_month & m_week]

    return ds

df['c'] = None
for idx in dr.index:
    labels = get_label_indices_by_period_id(df.index, idx.year, by_week=idx.week)
    print(labels)
    df.loc[labels, 'c'] = dr.loc[idx, 'a']

print(df)



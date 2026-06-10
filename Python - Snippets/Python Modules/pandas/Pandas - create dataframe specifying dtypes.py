"""
y, Pandas - create dataframe specifying dtypes.py, 2017.6.1
"""

import pandas as pd

def yDataFrame(*args, **kwargs):
    """ y, 2017.6.1 """

    _dtypes = 'dtypes'

    if _dtypes in kwargs:
        dtypes = kwargs[_dtypes]
        kwargs.pop(_dtypes)

    df = pd.DataFrame(*args, **kwargs)
    if 'dtypes' in locals():
        for key, value in dtypes.items():
            df = df.astype(dtype={key: value})

    return df

df = yDataFrame(columns=['int', 'str', 'float'], dtypes={
    'int': int, 'str': str, 'float': float
})
print(df)
print(df.dtypes)
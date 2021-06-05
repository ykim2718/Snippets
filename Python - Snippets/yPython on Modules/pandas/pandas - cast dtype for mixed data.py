"""
y, pandas - cast dtype for mixed data.py, 2018.11.20
"""

import pandas as pd

def _is_number_string(x):
    """ y, 2018.9.29, 10.16 """

    try:
        return float(x) == float(x)
    except:
        return False

col_name = 'A'
frame = pd.DataFrame({col_name: [1, 0, None, 'Null', float('nan')]})
print(frame, frame.dtypes)

mask = frame[col_name].apply(_is_number_string).astype(bool)
frame[col_name] = frame[col_name].astype(str)
frame.loc[mask, col_name] = frame[col_name][mask].astype(float)
print(frame, frame.dtypes)

for v in frame[col_name]:
    print(v, type(v))




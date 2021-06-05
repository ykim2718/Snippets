"""
y, 2020.3.3 - 4
pandas - astype with mask.py
"""

import pandas as pd

frame = pd.DataFrame(dict(a=['abc', '2020-3-3']))
print(frame.dtypes)
mask = pd.Series([False, True])
if False:
    frame.loc[mask, 'a'] = frame['a'][mask].astype('datetime64')
else:
    series = frame.a
    frame.a = series[mask].astype('datetime64')  # putting astype() first is important, 2020.3.3
    if (~mask).sum():
        frame.loc[~mask, 'a'] = series[~mask]
print(frame)
print(frame.dtypes)
for value in frame.a:
    print(f"type({value})={type(value)}")

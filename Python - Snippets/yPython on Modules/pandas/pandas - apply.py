"""
y, 2016.9.21, pandas - apply.py
"""
import pandas as pd

print("\n >>> 2016.9.21 <<<")
df = pd.DataFrame({'a': [x for x in range(2, 7, 1)],
                   'b': [x for x in range(4, 9, 1)],
                   'c': [x for x in range(5, 0, -1)]})
print(df)
dx = df[['a', 'b']].apply(lambda s: print(type(s), len(s), s))
print(dx)

print("\n >>> 2016.9.21 <<<")

def on_track_func(index, row):
    assert type(row) == pd.Series
    row['c'] *= 10
    row['d'] = 'on track'
    return row

def off_track_func(index, row):
    assert isinstance(row, pd.Series)
    row['e'] = 'off track'  # <<< No working because replacing a row is limited to the existing columns
    return row

def tracking_func(index, row):
    return True if index > 2 else False

df['d'] = None
on_track = False
for index, row in df.iterrows():
    on_track = tracking_func(index, row)
    df.loc[index, :] = on_track_func(index, row) if on_track else off_track_func(index, row)
print(df)



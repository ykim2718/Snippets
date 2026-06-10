import pandas as pd

df = pd.DataFrame({'a': [1, 2, 3]}, index=[4, 5, 6])
dg = df.loc[5:6]
dg.is_copy = 0  # great !! to avoid so many caveats
# dg['b'] = None
dg.loc[:, 'b'] = None

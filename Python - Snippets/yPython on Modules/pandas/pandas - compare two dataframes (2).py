"""
y, pandas - compare two dataframes (2).py, 2018.3.24
https://stackoverflow.com/questions/20225110/comparing-two-dataframes-and-getting-the-differences
"""

import pandas as pd

df1 = pd.DataFrame({'Buyer': ['Carl', 'Carl', 'Carl'], 'Quantity': [99, 3, 5, ]})
df2 = pd.DataFrame({'Buyer': ['Carl', 'Mark', 'Carl', 'Carl'], 'Quantity': [99, 1, 18, 5]})
print(df1)
print(df2)

df = pd.concat([df1, df2])
df = df.reset_index(drop=True)
df_gpby = df.groupby(list(df.columns))
idx = [x[0] for x in df_gpby.groups.values() if len(x) == 1]
df = df.reindex(idx)
df = df.reset_index(drop=True)
print(df)
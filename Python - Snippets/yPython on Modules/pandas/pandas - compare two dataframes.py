"""
y, Pandas - compare two dataframes.py, 2017.9.3, 9.5

Pandas: Diff of two dataframes

"""

import pandas as pd

df1 = pd.DataFrame({'Buyer': ['Carl', 'Carl', 'Carl'], 'Quantity': [99, 3, 5, ]})
df2 = pd.DataFrame({'Buyer': ['Carl', 'Mark', 'Carl', 'Carl'], 'Quantity': [99, 1, 18, 5]})

print(df1)
print(df2)

merged = df1.merge(df2, indicator=True, how='outer')
print(merged)
# print(merged[merged['_merge'] == 'right_only'])

diff = set(zip(df2.Buyer, df2.Quantity)) - set(zip(df1.Buyer, df1.Quantity))
print(diff)


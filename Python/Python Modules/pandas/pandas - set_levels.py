"""
y, 2025.1.16
pandas - set_levels.py
"""

import pandas as pd

# Create a sample DataFrame
arrays = [['A', 'A', 'B', 'B'], ['one', 'two', 'one', 'two']]
index = pd.MultiIndex.from_arrays(arrays, names=('level_0', 'level_1'))
df = pd.DataFrame([[1, 2, 3, 4], [5, 6, 7, 8]], columns=index)

print("Original DataFrame:")
print(df)

if False:
    # Define the new level 1 column names with unique values
    new_level_1_names = ['one_new_A', 'two_new_A', 'one_new_B', 'two_new_B']
else:
    # Define the new level 1 column names
    # new_level_1_names = ['one_new', 'two_new', 'one_new', 'two_new']
    # ValueError: Level values must be unique: ['one_new', 'two_new', 'one_new', 'two_new'] on level 1
    new_level_1_names = ['one_new', 'two_new']

# Set the new level 1 column names
df.columns = df.columns.set_levels(new_level_1_names, level=1)

print("DataFrame with replaced level 1 column names:")
print(df)

"""
y, pandas - rearrange.py, 2019.10.1
"""


import pandas as pd


index = pd.Index(['Summer', 'Winter', 'Spring', 'Fall'])
frame = pd.DataFrame([1, 2, 3, 4], index=index)
print(frame)

frame = frame.loc[['Spring', 'Summer', 'Fall', 'Winter']]
print(frame)

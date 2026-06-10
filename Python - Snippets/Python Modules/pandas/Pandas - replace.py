"""
y, 2016.7.20, Pandas - replace.py
"""
import pandas as pd

df = pd.DataFrame({
    'c1': [1, 2, 3],
    'c2': [4, 5, 6],
    'c3': [7, 8, 9],
    'c4': ['a', 'b', 'c'],
    'c5': ['d', 'e', 'f']
})

print(df.replace({'a': 'A', 'b': 'BB'}))

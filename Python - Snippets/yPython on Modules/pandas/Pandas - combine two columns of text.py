"""
y, 2016.7.15, Pandas - combine two columns of text.py

http://stackoverflow.com/questions/11858472/pandas-combine-string-and-int-columns
http://stackoverflow.com/questions/19377969/combine-two-columns-of-text-in-dataframe-in-pandas-python
"""
import pandas as pd

df = pd.DataFrame({
    'c1': [1, 2, 3],
    'c2': [4, 5, 6],
    'c3': [7, 8, 9],
}, index=['r1', 'r2', 'r3'])

df['new1'] = df['c1'].map(str) + df['c2'].map(str)
df['new2'] = df[['c1', 'c2']].apply(lambda x: '{},{}'.format(x[0], x[1]), axis=1)
df['new3'] = df[['c1', 'c2']].apply(lambda x: '%s' % x, axis=1)

print(df)

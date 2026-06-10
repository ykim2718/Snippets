"""
y, 2020.3.25
pandas - about _metadata.py
https://pandas.pydata.org/pandas-docs/stable/development/extending.html
"""

import pandas as pd
import pathlib

a = pd.DataFrame([1, 2, 3])
a._metadata = dict(Hello='world ...')
file_path = pathlib.Path(__file__).with_suffix('.pkl')
compression = 'gzip'
a.to_pickle(file_path, compression=compression)

b = pd.read_pickle(file_path, compression=compression)
print(b)
print(b._metadata)

"""
y, Pandas - to html.py, 2017.5.17

Python Pandas Data Frame save as HTML page
http://stackoverflow.com/questions/32430009/python-pandas-data-frame-save-as-html-page

"""

import pandas as pd
import numpy as np
import os

df = pd.DataFrame({'foo1': np.random.randn(2),
                   'foo2': np.random.randn(2)})

file_path = 'pandas - to html.html'

df.to_html(file_path,
           justify='left',
           float_format=lambda x: '%.3g' % x)

os.startfile(file_path)


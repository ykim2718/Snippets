"""
y, 2022.6.13
pandas - style - bar.py
https://pandas.pydata.org/pandas-docs/stable/user_guide/style.html
"""

import pandas as pd
from pandas.io.formats.style import Styler
import numpy as np
import bs4
import pathlib

np.random.seed(0)
df = pd.DataFrame(np.random.randn(5, 4), columns=['A', 'B', 'C', 'D'])
df.loc[3, 'A'] = 'text'  # causes TypeError: '<=' not supported between instances of 'float' and 'str'
df.loc[4, 'A'] = np.nan
print(df)

a = df.applymap(lambda x: np.nan if isinstance(x, float) else x).dropna(how='all', axis=0).dropna(how='all', axis=1)
df = df.applymap(lambda x: x if isinstance(x, float) else np.nan)

styler = Styler(df, uuid_len=0)
styler.bar(subset=['A', 'B'], align='mid', color=['#d65f5f', '#5fba7d'])\
    .format(na_rep='MISSING')
html = styler.render()

html = bs4.BeautifulSoup(html, 'html.parser').prettify()
# if compress_html:
#     html = re.sub('<td>\s*</td>', '<td/>', html)

pathlib.Path(__file__).with_suffix('.html').write_text(html)

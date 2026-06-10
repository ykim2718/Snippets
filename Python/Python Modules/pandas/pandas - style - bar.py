"""
y, 2022.6.13 - 14
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
print(f"{df=}")

a = df.applymap(lambda x: np.nan if isinstance(x, float) else x).dropna(how='all', axis=0).dropna(how='all', axis=1)
df = df.applymap(lambda x: x if isinstance(x, float) else np.nan)
print(f"{a=}")

styler = Styler(df, uuid_len=0)
styler.bar(subset=['A', 'B'], align='mid', color=['#d65f5f', '#5fba7d'])\
    .format(na_rep='MISSING')
html = styler.render()

soup = bs4.BeautifulSoup(html, 'html.parser')
for r in a.index:
    for c in a.columns:
        saved = a.loc[r, c]
        if saved:
            j, k = df.index.get_loc(r), df.columns.get_loc(c)
            v = soup.select(f"#T__row{j}_col{k}")[0].text
            print(f"{r=}, {c=}, {v=}")
            soup.select(f"#T__row{j}_col{k}")[0].string = saved

html = soup.prettify()

pathlib.Path(__file__).with_suffix('.html').write_text(html)

"""
y, 2021.8.15
pandas - style - set_table_styles.py
https://pandas.pydata.org/docs/reference/api/pandas.io.formats.style.Styler.set_table_styles.html
"""

import pandas as pd
import pathlib

a = pd.DataFrame(dict(a=[1, 2], b=[3, 4], c=[pd.Timestamp.now()] * 2))

# FIXME !!! # html = self.styler.set_td_classes(classes=["table-bordered", "table-striped", "table-hover"]).render()

a = a.style\
    .set_table_styles([{'selector': 'tr', 'props': 'background-color: yellow; font-size: 1em;'}])\
    .format(({'c': "{:%y-%m-%d}"}))
html = a.render()

pathlib.Path(__file__).with_suffix('.html').write_text(html)

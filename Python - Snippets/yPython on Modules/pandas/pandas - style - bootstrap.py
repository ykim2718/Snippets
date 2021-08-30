"""
y, 2021.8.30
pandas - style - bootstrap.py
https://pandas.pydata.org/docs/reference/api/pandas.io.formats.style.Styler.html
https://stackoverflow.com/questions/61740225/bootstrap-css-and-pandas-dataframe-to-html-how-to-add-class-to-thead
https://stackoverflow.com/questions/15643037/how-do-i-change-the-hover-over-color-for-a-hover-over-table-in-bootstrap
"""

import pandas as pd
from pandas.io.formats.style import Styler
import pathlib

now = pd.Timestamp.now()
if False:
    frame = pd.DataFrame(dict(a=[1, 2], b=[333, 4], c=[now] * 2))
else:
    frame = pd.DataFrame([[1, 333, now], [2, 4, now]],
                         columns=pd.MultiIndex.from_tuples([('A', 'a'), ('A', 'b'), ('B', 'c')]))
print(f"frame.shape={frame.shape}")

# css = pd.DataFrame(dict(a=['A-class'] * 2, b=['B-class'] * 2, c=['C-class'] * 2))
css = pd.DataFrame('Z-class', index=frame.index, columns=frame.columns)
print(f"css.shape={css.shape}")

html = Styler(frame, uuid="_", cell_ids=False) \
    .set_table_attributes('class="table table-hover table-sm text-right" style="font-size: 2em;"') \
    .set_td_classes(css) \
    .render() \
    .replace('<thead>', '<thead class="thead-light">', 1)

html = f"""
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css"
 integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
<style>
.table tbody tr:hover td, .table tbody tr:hover th {{
    background: yellow;
}}
</style>
<div class="d-inline-flex p-2" style="padding-left: 1em;">
{html}
</div>
"""

pathlib.Path(__file__).with_suffix('.html').write_text(html)

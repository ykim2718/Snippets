"""
y, 2021.8.28
plotly - text.py
https://plotly.com/python/horizontal-vertical-shapes/
"""

import plotly.express as px

df = px.data.stocks(indexed=True)
fig = px.line(df)
fig.add_hline(y=1, line_dash="dot",
              annotation_text="Jan 1, 2018 baseline",
              annotation_position="bottom right")
fig.add_vrect(x0="2018-09-24", x1="2018-12-18",
              annotation_text="decline", annotation_position="top left",
              fillcolor="green", opacity=0.25, line_width=0)

if False:
    fig.show()
else:
    import pathlib
    fig.write_html(str(pathlib.Path(__file__).with_suffix('.html')), auto_open=True)
"""
y, 2020.12.17
ploty - basic scatter plot.py
https://plotly.com/python/line-and-scatter/
    .. Set size and color with column names
"""

import plotly.io as pio
print(pio.renderers.default)

import plotly.express as px
df = px.data.iris()
fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species",
                 size='petal_length', hover_data=['petal_width'])
# fig.show()
import pathlib
fig.write_html(str(pathlib.Path(__file__).with_suffix('.html')), auto_open=True)
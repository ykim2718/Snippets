"""
y, 2021.8.28
plotly - rectangle.py
https://plotly.com/python/horizontal-vertical-shapes/
"""

import plotly.express as px

df = px.data.iris()
fig = px.scatter(df, x="petal_length", y="petal_width")
fig.add_hline(y=0.9)
fig.add_hrect(y0=0.9, y1=2.6, line_width=0, fillcolor="red", opacity=0.2)
fig.show()

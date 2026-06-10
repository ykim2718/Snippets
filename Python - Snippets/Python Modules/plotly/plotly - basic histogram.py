"""
y, 2020.12.22
plotly - basic histogram.py
https://plotly.com/python/distplot/
"""

import plotly.express as px

df = px.data.tips()
print(df.head())
fig = px.histogram(df, x="total_bill", y="tip", color="sex",
                   marginal="box",  # or violin, rug
                   hover_data=df.columns)
fig.show()

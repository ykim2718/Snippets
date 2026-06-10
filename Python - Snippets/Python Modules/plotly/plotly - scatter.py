"""
y, 2021.8.28
plotly - scatter.py
https://plotly.com/python/figure-labels/
https://plotly.com/python/marker-style/
https://plotly.com/python/figure-labels/
https://plotly.com/python/marker-style/
"""


import plotly.graph_objects as go

fig = go.Figure()

fig.add_trace(go.Scatter(
    x=[0, 1, 2, 3, 4, 5, 6, 7, 8],
    y=[0, 1, 2, 3, 4, 5, 6, 7, 8],
    name="Name of Trace 1"       # this sets its legend entry
))


fig.add_trace(go.Scatter(
    x=[0, 1, 2, 3, 4, 5, 6, 7, 8],
    y=[1, 0, 3, 2, 5, 4, 7, 6, 8],
    name="Name of Trace 2",
    mode='lines+markers',
    marker=dict(
        color='LightSkyBlue',
        size=20,
        line=dict(
            color='MediumPurple',
            width=2
        )
    ),
    marker_symbol='square-open-dot',
    showlegend=True
))

fig.update_layout(
    title="Plot Title",
    xaxis_title="X Axis Title",
    yaxis_title="Y Axis Title",
    legend_title="Legend Title",
    font=dict(
        family="Courier New, monospace",
        size=18,
        color="RebeccaPurple"
    )
)

if False:
    fig.show()
else:
    import pathlib
    fig.write_html(str(pathlib.Path(__file__).with_suffix('.html')), auto_open=True)
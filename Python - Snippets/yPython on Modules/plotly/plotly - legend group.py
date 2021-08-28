"""
y, 2021.8.28
plotly - legend group x.py
https://plotly.com/python/legend/
"""

import plotly.graph_objects as go

fig = go.Figure()

fig.add_trace(go.Scatter(
    x=[1, 2, 3],
    y=[2, 1, 3],
    legendgroup="group",  # this can be any string, not just "group"
    legendgrouptitle_text="First Group Title",
    name="first legend group",
    mode="markers",
    marker=dict(color="Crimson", size=10)
))

fig.add_trace(go.Scatter(
    x=[1, 2, 3],
    y=[2, 2, 2],
    legendgroup="group",
    name="first legend group - average",
    mode="lines",
    line=dict(color="Crimson")
))

fig.add_trace(go.Scatter(
    x=[1, 2, 3],
    y=[4, 9, 2],
    legendgroup="group2",
    legendgrouptitle_text="Second Group Title",
    name="second legend group",
    mode="markers",
    marker=dict(color="MediumPurple", size=10)
))

fig.add_trace(go.Scatter(
    x=[1, 2, 3],
    y=[5, 5, 5],
    legendgroup="group2",
    name="second legend group - average",
    mode="lines",
    line=dict(color="MediumPurple")
))

fig.update_layout(
    title="Try Clicking on the Legend Items!",
    legend_tracegroupgap=50,
)

if False:
    fig.show()
else:
    import pathlib
    fig.write_html(str(pathlib.Path(__file__).with_suffix('.html')), auto_open=True)

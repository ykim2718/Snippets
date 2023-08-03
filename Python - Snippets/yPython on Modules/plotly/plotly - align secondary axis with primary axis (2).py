"""
y, 2023.8.1, 8.3
plotly - align secondary axis with primary axis (2).py
https://www.appsloveworld.com/python/717/align-secondary-percentage-y-axis-with-primary-y-axis-in-plotly
https://plotly.com/python/axes/
    . Rangemode: normal, tozero, nonnegative
    . Fixed Ratio Axes: scaleanchor, scaleratio
https://stackoverflow.com/questions/62030735/how-to-obtain-generated-x-axis-and-y-axis-range-in-plotly-plot
    . Getting the axis range from a plotly plot is not possible within the python implementation.
https://plotly.com/python/tick-formatting/
https://plotly.com/python/multiple-axes/  ★
https://plotly.com/python/multiple-axes/#sync-axes-ticks ★★
https://stackoverflow.com/questions/62182445/what-does-overlaying-parameter-of-layout-axis-object-of-plotly-mean
"""

import plotly
import plotly.graph_objects as go
from plotly.subplots import make_subplots

# Create figure with secondary y-axis
fig = make_subplots(
    rows=2, cols=1, row_heights=[1, 2],  vertical_spacing=0.01,
    shared_xaxes=True, specs=[[{'secondary_y': False}]] + [[{'secondary_y': True}]]
)

# Add traces
fig.add_trace(
    go.Scatter(x=[1, 2, 3], y=[40, 50, 100], name="y"),
    row=1, col=1, secondary_y=False,
)
fig.add_trace(
    go.Scatter(x=[2, 3, 4], y=[4, 5, 4], name="y2"),
    row=2, col=1, secondary_y=False,
)
fig.add_trace(
    go.Scatter(x=[1.5, 2.5, 3.5], y=[4, 3, 2], name="y3"),
    row=2, col=1, secondary_y=True
)

# Add titles
fig.update_layout(title_text="Double Y Axis Example")
fig.update_xaxes(title_text="xaxis title")
fig.update_yaxes(title_text="<b>primary</b> yaxis title", secondary_y=False)
fig.update_yaxes(title_text="<b>secondary</b> yaxis title", secondary_y=True)

# Align y axis
assert plotly.__version__ >= '5.15.0', 'not certain of version but need recent one :<'


def find_axis_id_by_title_text(fig, title_text, which='y') -> str:
    """ y, 2023.8.3 """

    assert isinstance(fig,  plotly.graph_objects.Figure)
    assert which in ['x', 'y']

    keys = list(fig.layout)
    keys = [key for key in keys if key.startswith(f"{which}axis")]
    for key in keys:
        if ax := getattr(fig.layout, key):
            if ax.title.text == title_text:
                return key
    return ''


axis_id = find_axis_id_by_title_text(fig, "<b>secondary</b> yaxis title", which='y')
print(f"{axis_id=}")

fig.update_layout(**{axis_id: dict(tickmode="sync")})


fig.show()

"""
y, 2023.8.1
plotly - align secondary axis with primary axis.py
https://www.appsloveworld.com/python/717/align-secondary-percentage-y-axis-with-primary-y-axis-in-plotly
https://plotly.com/python/axes/
    . Rangemode: normal, tozero, nonnegative
    . Fixed Ratio Axes: scaleanchor, scaleratio
"""

import plotly.graph_objects as go
from plotly.subplots import make_subplots
import numpy as np

# Create figure with secondary y-axis
fig = make_subplots(specs=[[{"secondary_y": True}]])

# Add traces
fig.add_trace(
    go.Scatter(x=[1, 2, 3], y=[40, 50, 100], name="yaxis data"),
    secondary_y=False,
)

fig.add_trace(
    go.Scatter(x=[2, 3, 4], y=[4, 5, 4], name="yaxis2 data"),
    secondary_y=True,
)

# Add figure title
fig.update_layout(
    title_text="Double Y Axis Example"
)

# Set x-axis title
fig.update_xaxes(title_text="xaxis title")

# Set y-axes titles
fig.update_yaxes(title_text="<b>primary</b> yaxis title", secondary_y=False)
fig.update_yaxes(title_text="<b>secondary</b> yaxis title", secondary_y=True)

# align_secondary_y_axis
if set_tick_values := False:
    fig.update_layout(yaxis1_tickvals=[40, 70, 100], yaxis2_tickvals=[4, 4.5, 5])
if set_scaling := True:
    ax1, axt = fig.data[0], fig.data[1]
    y0_range = np.nanmin(ax1.y), np.nanmax(ax1.y)  # primary axis
    y1_range = np.nanmin(axt.y), np.nanmax(axt.y)  # primary axis
    scaler_ratio = (np.diff(y1_range) / np.diff(y0_range))[0]
    print(f"{y0_range=}")
    print(f"{y1_range=}")
    print(f"{scaler_ratio=}")
    fig.update_yaxes(
        rangemode='normal', scaleanchor=axt.yaxis, scaleratio=scaler_ratio, constraintoward='bottom')
    # FIXME !!! how to set tick count at both two axes

fig.show()

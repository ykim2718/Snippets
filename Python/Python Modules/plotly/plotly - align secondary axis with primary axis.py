"""
y, 2023.8.1, 8.3
plotly - align secondary axis with primary axis.py
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
import numpy as np
import math
import typing

# Create figure with secondary y-axis
fig = make_subplots(specs=[[{"secondary_y": True}]])

# Add traces
fig.add_trace(
    go.Scatter(x=[1, 2, 3], y=[40, 50, 100], name="y"),
    secondary_y=False,
)

fig.add_trace(
    go.Scatter(x=[2, 3, 4], y=[4, 5, 4], name="y2"),
    secondary_y=True,
)

if True:
    fig.add_trace(
        go.Scatter(x=[1.5, 2.5, 3.5], y=[4, 3, 2], name="y3"),
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


def power_number(f):
    """
    y,  2016.11.6
        2018.6.11

    Example
    -------
    >> print(power_number(1.2))
        0
    >> print(power_number(12))
        1
    """

    if f > 0 and np.isfinite(f):
        return int(np.log10(f) // 1)
    else:
        return np.nan


def round_to_nearest(f, precision):
    """
    y,  2016.10.19
        2017.6.12, 11.4

    Example
    -------
    >> round_to_nearest(0.12345, 0.01)
        0.12
    >> round_to_nearest(4, 5)
        5
    >> round_to_nearest(9, 5)
        10
    """

    if np.isfinite(f) and np.isfinite(precision):
        #return int(f / precision + 0.5 * f / abs(f)) * precision
        return round(float(f) / precision) * precision
    else:
        return np.nan


def calculate_tick_interval(
    ll, ul, min_count=2, max_count=9, return_count=False
) -> typing.Union[typing.Union[int, float], typing.Union[int, float], int]:
    """
    y,  2017.1.5, 12.25
        2023.8.1
    """

    assert ll <= ul

    # 2017.12.25
    if ll == ul:
        return ll, ul

    max_of_the_two = max(abs(ll), abs(ul))
    interval = 10 ** power_number(max_of_the_two)
    difference = ul - ll  # 2017.12.25
    count = difference / interval
    if min_count <= count <= max_count:
        pass
    elif count < min_count:
        while (difference / interval) < min_count:
            interval /= 2
        interval = round_to_nearest(interval, 10 ** power_number(interval))  # 2017.12.25
    elif max_count < count:
        while max_count < (difference / interval):
            interval *= 2
        interval = round_to_nearest(interval, 10 ** power_number(interval))  # 2017.12.25

    if return_count:
        return interval, math.ceil(difference / interval) + 1
    else:
        return interval


# align_secondary_y_axis
approach = 'set_tickmode_sync'

if approach == 'set_tick_values':
    if False:
        fig.update_layout(yaxis1_tickvals=[40, 70, 100], yaxis2_tickvals=[4, 4.5, 5])
    else:
        ax1, axt = fig.data[0], fig.data[1]
        y0_range = np.nanmin(ax1.y), np.nanmax(ax1.y)  # primary axis
        y1_range = np.nanmin(axt.y), np.nanmax(axt.y)  # secondary axis
        y0_tick_interval, y0_tick_count = calculate_tick_interval(*y0_range, max_count=9, return_count=True)
        y1_tick_interval, y1_tick_count = calculate_tick_interval(*y1_range, max_count=9, return_count=True)
        tick_count = max(y0_tick_count, y1_tick_count)
        margin = 1
        y0_ticks = [y0_range[0] + y0_tick_interval * j for j in range(-margin, tick_count + margin)]
        y1_ticks = [y1_range[0] + y1_tick_interval * j for j in range(-margin, tick_count + margin)]
        fig.update_layout(
            yaxis=dict(tickmode='array', tickvals=y0_ticks, ticktext=[str(x) for x in y0_ticks],
                       range=[y0_ticks[0], y0_ticks[-1]]),
            yaxis2=dict(tickmode='array', tickvals=y1_ticks, ticktext=[str(x) for x in y1_ticks],
                        range=[y1_ticks[0], y1_ticks[-1]])
        )
        print(f"{y0_tick_interval=}, {y0_tick_count=}, {y0_ticks=}")
        print(f"{y1_tick_interval=}, {y1_tick_count=}, {y1_ticks=}")

if approach == 'set_tickmode_sync':
    assert plotly.__version__ >= '5.15.0', 'not certain of version but need recent one :<'
    fig.update_layout(
        yaxis2=dict(
            # title=dict(text="Right Axis"),
            # side="right",
            tickmode="sync",
            # overlaying="y",
        ),
    )


fig.show()

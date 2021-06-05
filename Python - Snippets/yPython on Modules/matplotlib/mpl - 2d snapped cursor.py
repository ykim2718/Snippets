"""
y (copyRight) 2016.9.9, mpl - 2d snapped cursor.py
matplotlib widgets - matplotlib.widgets
http://matplotlib.org/api/widgets_api.html
find nearest value in numpy array
http://stackoverflow.com/questions/2566412/find-nearest-value-in-numpy-array
pylab_examples example code: cursor_demo.py
http://matplotlib.org/1.3.1/examples/pylab_examples/cursor_demo.html
* Finding the closest point to a list of points
http://codereview.stackexchange.com/questions/28207/finding-the-closest-point-to-a-list-of-points
"""
from matplotlib.widgets import Cursor
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl


from scipy.spatial.distance import cdist

def closest_node(node, nodes):
    return nodes[cdist([node], nodes).argmin()]


def on_mouse_move_for_control_of_cursor(event):
    if not event.inaxes: return
    fig = event.canvas.figure
    node = [event.xdata, event.ydata]
    x_array = fig.get_axes()[0].lines[0].get_xdata()
    y_array = fig.get_axes()[0].lines[0].get_ydata()
    nodes = list(zip(x_array, y_array))
    x, y = closest_node(node, nodes)
    print(event, node, x, y)
    event.xdata, event.ydata = x, y
    cursor.onmove(event)
    return


fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, axisbg='#FFFFCC')

x, y = 4*(np.random.rand(2, 100) - .5)
ax.plot(x, y, 'o')
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2)

# set useblit = True on gtkagg for enhanced performance
cursor = Cursor(ax, useblit=True, color='red', linewidth=2)
fig.canvas.mpl_connect('motion_notify_event', on_mouse_move_for_control_of_cursor)

plt.show()


"""
http://stackoverflow.com/questions/4999014/matplotlib-pyplot-how-to-zoom-subplots-together-and-x-scroll-separately
y, 2016.4.28
"""
from matplotlib import pyplot
import numpy

x = numpy.linspace(0, 10, 100)
y = numpy.sin(x) * (1 + x)

fig = pyplot.figure()
ax1 = pyplot.subplot(121)
ax1.plot(x, y)
ax2 = pyplot.subplot(122)
ax2.plot(x, y)

ax1.old_xlim = ax1.get_xlim()  # store old values so changes
ax2.old_xlim = ax2.get_xlim()  # can be detected


def re_zoom(event):
    zoom = 1.0
    for ax in event.canvas.figure.axes:  # get the change in scale
        nx = ax.get_xlim()
        ox = ax.old_xlim
        if ox != nx:  # of axes that have changed scale
            zoom = (nx[1] - nx[0]) / (ox[1] - ox[0])

    for ax in event.canvas.figure.axes:  # change the scale
        nx = ax.get_xlim()
        ox = ax.old_xlim
        if ox == nx:  # of axes that need an update
            mid = (ox[0] + ox[1]) / 2.0
            dif = zoom * (ox[1] - ox[0]) / 2.0
            nx = (mid - dif, mid + dif)
            ax.set_xlim(*nx)
        ax.old_xlim = nx
    if zoom != 1.0:
        event.canvas.draw()  # re-draw the canvas (if required)


pyplot.connect('motion_notify_event', re_zoom)  # for right-click pan/zoom
pyplot.connect('button_release_event', re_zoom)  # for rectangle-select zoom
pyplot.show()

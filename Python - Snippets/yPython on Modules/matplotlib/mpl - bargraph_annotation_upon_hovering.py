"""
y, 2021.3.11
mpl - bargraph_annotation_upon_hovering.py
https://gist.github.com/eboisseau/d5a3e4ebdf0659292be51594aaa29fd2
https://stackoverflow.com/questions/7908636/possible-to-make-labels-appear-when-hovering-over-a-point-in-matplotlib
"""

import matplotlib.pyplot as plt

# input data
x = [2010, 2011, 2012, 2013]
y = [13, 17, 42, 4]

# create and define plot
fig, ax = plt.subplots()
graph = plt.bar(x, y)
plt.xticks(x)

# define the tooltip
annot = ax.annotate("", xy=(0, 0), xytext=(20, 20), textcoords="offset points",
                    bbox=dict(boxstyle="round", fc="w"),
                    arrowprops=dict(arrowstyle="->"))
annot.set_visible(False)


def update_annot(artist):
    """ update tooltip when hovering a given plotted objet """

    # in plt.bar, each artist is a Rectangle – see https://matplotlib.org/api/_as_gen/matplotlib.patches.Rectangle.html
    # find the middle of the bar
    center_x = artist.get_x() + artist.get_width() / 2
    center_y = artist.get_y() + artist.get_height() / 2
    annot.xy = (center_x, center_y)
    # get the height of the bar as text
    text = str(artist.get_height())
    annot.set_text(text)
    annot.get_bbox_patch().set_alpha(0.4)


def hover(event):
    """ update and show a tooltip while hovering an object; hide it otherwise """
    vis = annot.get_visible()
    if event.inaxes == ax:
        an_artist_is_hovered = False
        for artist in graph:
            contains, _ = artist.contains(event)
            if contains:
                an_artist_is_hovered = True
                update_annot(artist)
                annot.set_visible(True)
                fig.canvas.draw_idle()
        if not an_artist_is_hovered:
            # one wants to hide the annotation only if no artist in the graph is hovered
            annot.set_visible(False)
            fig.canvas.draw_idle()


# call 'hover' if there is a mouse motion
fig.canvas.mpl_connect("motion_notify_event", hover)

# time to see our work!
plt.show()

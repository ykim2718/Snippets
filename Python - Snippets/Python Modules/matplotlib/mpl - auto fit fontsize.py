"""
y, 2022.3.21
mpl - auto fit fontsize.py
https://stackoverflow.com/questions/5320205/matplotlib-text-dimensions
"""

import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib.transforms import Bbox


def auto_fit_fontsize(text, width, height, fig=None, ax=None):
    '''Auto-decrease the fontsize of a text object.

    Args:
        text (matplotlib.text.Text)
        width (float): allowed width in data coordinates
        height (float): allowed height in data coordinates
    '''

    assert isinstance(text, mpl.text.Text)

    fig = fig or plt.gcf()
    ax = ax or plt.gca()

    # get text bounding box in figure coordinates
    renderer = fig.canvas.get_renderer()
    bbox_text = text.get_window_extent(renderer=renderer)

    # transform bounding box to data coordinates
    bbox_text = Bbox(ax.transData.inverted().transform(bbox_text))

    # evaluate fit and recursively decrease fontsize until text fits
    fits_width = bbox_text.width < width if width else True
    fits_height = bbox_text.height < height if height else True
    if not all((fits_width, fits_height)):
        text.set_fontsize(text.get_fontsize() - 1)
        auto_fit_fontsize(text, width, height, fig, ax)


fig, ax = plt.subplots()
ax.bar(0.5, 0.5, width=0.5)
text = ax.text(0.5, 0.5, "0.5 (50.00 percent)", va='top', ha='center', fontsize=12)
print(f"{type(text)=}")
ax.set_xlim(-0.5, 1.5)
auto_fit_fontsize(text, 0.5, None, fig=fig, ax=ax)


plt.show()
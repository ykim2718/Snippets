"""
y, 2023.1.18
mpl - transformation from data to pixel.py
https://stackoverflow.com/questions/59794014/convert-pixel-coordinates-to-data-coordinates-in-matplotlib
https://www.tutorialspoint.com/determine-matplotlib-axis-size-in-pixels
"""

from matplotlib import pyplot as plt

fig, ax = plt.subplots()
print(f"{fig.dpi=}")
bbox = ax.get_window_extent().transformed(fig.dpi_scale_trans.inverted())
width, height = bbox.width, bbox.height
print(f"pixel limits: {bbox.width=}, {bbox.height=}")
print(f"data limits: {ax.get_xlim()=}, {ax.get_ylim()=}")

xxxx TODO 2023.1.18

x = 4.96, 3.696  # in pixel coordinates
print(f"{x=}")
point = ax.transData.inverted().transform(x)
print(f"{point=}")

ax.set_xlim(10, 10)
point = ax.transData.inverted().transform(x)
print(f"{point=}")

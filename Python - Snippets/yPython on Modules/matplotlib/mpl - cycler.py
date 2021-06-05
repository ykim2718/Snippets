"""
y, mpl - cycler.py, 2019.3.11
https://matplotlib.org/tutorials/intermediate/color_cycle.html
https://matplotlib.org/examples/color/color_cycle_demo.html
"""

from cycler import cycler

cc = (cycler(color=list('rgbcmk')) *
      cycler(linestyle=['-', '--', '-.']))
for d in cc:
    print(d)
"""
y, 2020.1.20
math - perpendicular distance.py
https://www.geeksforgeeks.org/perpendicular-distance-between-a-point-and-a-line-in-2-d/
"""

import math
import numpy as np


def shortest_distance(x1, y1, a, b, c):
    """
    y,  2020.1.20

    Note
    ----
    # distance between point p(x1, y1) and line ax + by + c = 0
    """

    d = abs((a * x1 + b * y1 + c)) / (math.sqrt(a * a + b * b))
    return d


def perpendicular_distance(x, y, slope, yi):
    """ y, 2020.1.20 """

    def _shortest_distance(array, a, b, c):
        return shortest_distance(array[0], array[1], a, b, c)

    x = np.array(x)
    y = np.array(y)
    a = np.stack((x, y))
    r = np.apply_along_axis(_shortest_distance, 0, a, -slope, 1, -yi)
    return r


x1 = 5
y1 = 6
a = -2
b = 3
c = 4
d = shortest_distance(x1, y1, a, b, c)
print(f"shortest distance is {d}")
slope, yi = -a / b, -c / b

d = perpendicular_distance([x1, 2], [y1, 3], slope, yi)
print(f"perpendicular distance is {d}")

"""
shortest distance is 3.328201177351375
perpendicular distance is [3.32820118 2.49615088]
"""

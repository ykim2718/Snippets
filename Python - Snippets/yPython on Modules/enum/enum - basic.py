"""
y, 2022.5.2
enum - basic.py
https://docs.python.org/3.7/library/enum.html
"""

from enum import Enum


class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3


print(Color.RED)  # Color.RED
print(repr(Color.RED))  # <Color.RED: 1
print(type(Color.RED))  # <enum 'Color'>
print(Color.RED == 1)  # FALSE
print(list(Color))  # [<Color.RED: 1>, <Color.GREEN: 2>, <Color.BLUE: 3>]
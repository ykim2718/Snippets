"""
y, 2022.5.2, 6.26
enum - basic.py
https://docs.python.org/3.7/library/enum.html
"""

from enum import Enum


class Color(Enum):
    RED = 1
    GREEN = 2
    BLUE = 3
    PINK = 'pink'


print(list(Color))  # [<Color.RED: 1>, <Color.GREEN: 2>, <Color.BLUE: 3>, <Color.PINK: 'pink'>]
print([e.name for e in Color])  # ['RED', 'GREEN', 'BLUE', 'PINK']

print(Color.RED)  # Color.RED
print(Color.RED.name)  # 'RED'
print(Color.RED.value)  # 1
print(str(Color.RED))  # 'Color.RED'
print(repr(Color.RED))  # <Color.RED: 1>
print(type(Color.RED))  # <enum 'Color'>
print(Color.RED == 1)  # FALSE
print(Color.RED in Color)  # True
# print('RED' in Color, '<<<<<<<<')  # TypeError: unsupported operand type(s) for 'in': 'str' and 'EnumMeta'

print(Color.PINK)  # Color.PINK
print(Color.PINK.name)  # 'PINK'
print(Color.PINK.value)  # pink
# print('PINK' in Color, '<<<<<<<<')  # TypeError: unsupported operand type(s) for 'in': 'str' and 'EnumMeta'

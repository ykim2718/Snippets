"""
y, 2021.2.23
python class - __slots__.py
https://stackoverflow.com/questions/472000/usage-of-slots
    .. 1. faster attribute access.
       2. space savings in memory.
"""


class Klass:
    __slots__ = ('A', 'B')  # remove __dict__ so that other attributes become read only; __slots__ = (), 2021.2.23
    # B = 2  # >> ValueError: 'B' in __slots__ conflicts with class variable
    C = 3


glass = Klass()

print(Klass.A)  # <member 'A' of 'Klass' objects>
print(glass.C)  # 3

try:
    print(glass.A)
except AttributeError as ex:
    print(ex.__class__.__name__, ':', str(ex))  # AttributeError : A

glass.B = 2
print(glass.B)  # 2

try:
    glass.C = 3
except AttributeError as ex:
    print(ex.__class__.__name__, ':', str(ex))  # AttributeError : 'Klass' object attribute 'C' is read-only

try:
    glass.D = 4
except AttributeError as ex:
    print(ex.__class__.__name__, ':', str(ex))  # AttributeError : 'Klass' object has no attribute 'D'

try:
    glass.__dict__
except AttributeError as ex:
    print(ex.__class__.__name__, ':', str(ex))  # AttributeError : 'Klass' object has no attribute '__dict__'


class Glass:
    __slots__ = ()


glass = Glass()
print(hasattr(Glass, '__dict__'))  # True
print(hasattr(glass, '__dict__'))  # False

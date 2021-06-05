"""
y, python isinstance - vs type.py, 2019.1.25, 6.18
https://stackoverflow.com/questions/1549801/what-are-the-differences-between-type-and-isinstance
"""


class Vehicle:
    pass


class Truck(Vehicle):
    pass


print(isinstance(Vehicle(), Vehicle))  # returns True
print(type(Vehicle()) == Vehicle)      # returns True
print(type(Vehicle()) is Vehicle)      # returns True
print(isinstance(Truck(), Vehicle))    # returns True
print(type(Truck()) == Vehicle)        # returns False, and this probably won't be what you want.
print(type(Truck()) is Vehicle)        # returns False, and this probably won't be what you want.

v = Vehicle()
t = Truck()
print(isinstance(v, Vehicle), isinstance(v, Truck))  # True, False
print(isinstance(t, Vehicle), isinstance(t, Truck))  # True, True

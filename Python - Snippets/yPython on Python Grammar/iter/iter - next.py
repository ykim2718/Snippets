"""
y, iter - next.py, 2019.1.29
https://www.geeksforgeeks.org/python-difference-iterable-iterator/
"""

# list of cities
cities = ["Berlin", "Vienna", "Zurich"]

# initialize the object
iterator_obj = iter(cities)

print(next(iterator_obj))
print(next(iterator_obj))
print(next(iterator_obj))
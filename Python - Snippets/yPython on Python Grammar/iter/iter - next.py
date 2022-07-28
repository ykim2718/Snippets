"""
y, 2019.1.29; 2022.7.28
iter - next.py
https://www.geeksforgeeks.org/python-difference-iterable-iterator/
"""

# list of cities
cities = ["Berlin", "Vienna", "Zurich"]

# initialize the object
iterator_obj = iter(cities)

print(next(iterator_obj))
for n in iterator_obj:
    print(f"{n=}")

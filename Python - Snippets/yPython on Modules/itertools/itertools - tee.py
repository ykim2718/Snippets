"""
y, itertools - tee.py, 2019.1.29
https://stackoverflow.com/questions/42132731/how-to-create-a-copy-of-python-iterator
"""

from itertools import tee

my_list = [5, 4, 3, 2]
first_it = iter(my_list)
first_it, second_it = tee(first_it)
print(next(first_it))   # prints 5
print(next(second_it))  # prints 5
print(next(first_it))   # prints 4

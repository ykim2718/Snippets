"""
y, itertools - slice list.py, 2018.7.10
"""

from itertools import islice

a_list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
n = 4
i_list = iter(a_list)
sliced_lists = iter(lambda: list(islice(i_list, n)), [])
for sliced_list in sliced_lists:
    print(sliced_list)
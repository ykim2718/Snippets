"""
y, python list - rank of a list.py, 2018.12.16
https://stackoverflow.com/questions/3071415/efficient-method-to-calculate-the-rank-vector-of-a-list-in-python
"""

a_list = [-1, 3, 2, 0, 0]
rank = [sorted(a_list).index(x) for x in a_list]
print(rank)

rank = [sorted(a_list, reverse=True).index(x) for x in a_list]
print(rank)

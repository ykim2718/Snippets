"""
y, 2022.5.2
bisect - basic.py
https://docs.python.org/3.7/library/
https://docs.python.org/3.7/library/bisect.html
"""


from bisect import bisect


def grade(score, breakpoints=[60, 70, 80, 90], grades='FDCBA'):
    i = bisect(breakpoints, score)
    return grades[i]


a = [grade(score) for score in [33, 99, 77, 70, 89, 90, 100]]
print(a)  # ['F', 'A', 'C', 'C', 'B', 'A', 'A']

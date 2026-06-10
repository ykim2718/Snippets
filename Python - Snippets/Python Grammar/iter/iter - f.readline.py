"""
y, iter - f.readline.py, 2018.9.28
https://docs.python.org/3/library/functions.html#iter
"""

import os

a_file = os.path.basename(__file__).replace('.py', '.txt')

with open(a_file, 'w') as f:
    for j in range(3):
        f.write(str(j) + '\n')

with open(a_file) as f:
    for line in iter(f.readline, ''):
        print(line.rstrip())
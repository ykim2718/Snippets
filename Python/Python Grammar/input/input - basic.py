"""
y, 2022.5.2 - 3
input - basic.py
"""

import sys

if True:
    input_file = 'input.txt'
    sys.stdin = open(input_file)
    input = sys.stdin.readline
else:
    input = input

q = int(input())
for _ in range(q):
    cmd = list(map(int, input().split()))
    print(cmd)

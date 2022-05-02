"""
y, 2022.5.2
input - basic.py
"""

import sys

if True:
    input_file = 'input.txt'
    sys.stdin = open('input.txt')
else:
    input = sys.stdin.readline

q = int(input())
for _ in range(q):
    cmd = list(map(int, input().split()))
    print(cmd)

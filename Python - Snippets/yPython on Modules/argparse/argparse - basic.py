"""
y, 2016.7.9; 2020.4.22
argparse - basic.py
http://stackoverflow.com/questions/7605631/passing-a-list-to-python-from-command-line
"""

import argparse

# Script Parameters: -details d1 d2 d3 --quickly  -t 4

parser = argparse.ArgumentParser()
parser.add_argument('-v', action='store_true')
parser.add_argument('-details', nargs='*')
parser.add_argument('-list', nargs='*')
parser.add_argument('-q', '--quickly', action='store_true')
parser.add_argument('-t', type=int, default=3)

if False:
    args = parser.parse_args(" -details d1 d2 d3 --quickly  -t 4".split())
else:
    args = parser.parse_args(" -details d1 d2 d3 -q -t 4".split())

print(args.details)
print(args.list)  # None
print(args.quickly)
print(args.t)

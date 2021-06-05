"""
y, argparse - action=append.py, 2019.1.27
"""

import sys

sys.argv += ['-append', '1', '2', '-append', '3']
print(sys.argv)

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-append', nargs='*', action='append')
args = parser.parse_args()

print(vars(args))
"""
y, argparse - nargs.py, 2019.1.24
"""

import sys

sys.argv += [str(j) for j in [1, 2, 3]]
print(sys.argv)

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('nums', nargs='*', default=[0])
args = parser.parse_args()

print("nums = {}".format(args.nums))
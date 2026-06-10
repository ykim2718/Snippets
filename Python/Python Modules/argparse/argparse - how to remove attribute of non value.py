"""
y, argparse - how to remove attribute of non value.py, 2019.11.19
https://stackoverflow.com/questions/57563483/parse-args-do-not-include-none-values-in-namespace
"""

import argparse

parser = argparse.ArgumentParser(prog='PROG', argument_default=argparse.SUPPRESS)
parser.add_argument('-x')
parser.add_argument('--foo')
ns = parser.parse_args(['-x', 'X'])
print(ns)

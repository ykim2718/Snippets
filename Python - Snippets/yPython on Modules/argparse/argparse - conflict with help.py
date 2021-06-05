"""
y, argparse - conflict with help.py, 2019.2.23
http://gnoownow10.cafe24.com/parse-known-args-with-help.html
"""

import sys

# sys.argv += ['-history', '1']
sys.argv += ['-h']
print(sys.argv)

import argparse

parser = argparse.ArgumentParser(add_help=False)
# parser.add_argument('-history', default=0)
parser.add_argument('--help', '-h', action='store_true', help='show this help message and exit');
args = parser.parse_args()

if args.help:
    parser.print_help()
    parser.exit()

print(vars(args))

# no problem to use option starting with 'h'
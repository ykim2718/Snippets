"""
y, argparse - subparsers.py, 2017.6.13, 6.15, 6.16

"""

import argparse

def handler_sub1(args):
    print(args)
    if args.s1:
        print('..sub1', args.s1)

parser = argparse.ArgumentParser()
parser.add_argument('-main', action='store_true')
parser.add_argument('-opt', nargs='*', type=int)
parser.add_argument('-', dest='_stop_optional_args', action='store_true', help=argparse.SUPPRESS)

subparsers = parser.add_subparsers(dest='subcommand')
subparser = subparsers.add_parser('sub1')
subparser.set_defaults(func=handler_sub1)
subparser.add_argument('-s1', action='store_true')
subparser = subparsers.add_parser('sub2')
subparser.add_argument('-s2', action='store_true')

# args = parser.parse_args("-main sub1 -sub1 sub2 -s2".split()) >> cause error 'unrecognized arguments: sub2 -s2'
args = parser.parse_args("-main sub1 -s1".split())
print(args.subcommand)

args = parser.parse_args("sub2 -s2".split())
print(args)

# subparser parsing with nargs='*'
args = parser.parse_args("-main -opt 1 2 - sub2 -s2".split())
print(args)

args = parser.parse_args("-main -opt 1 2 - sub2".split())
print(args.subcommand)

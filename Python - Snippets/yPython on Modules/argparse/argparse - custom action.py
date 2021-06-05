"""
y, argparse - custom action.py, 2018.2.15
https://stackoverflow.com/questions/4194948/python-argparse-is-there-a-way-to-specify-a-range-in-nargs
"""

import argparse

def required_length(nmin,nmax):
    class RequiredLength(argparse.Action):
        def __call__(self, parser, args, values, option_string=None):
            if not nmin<=len(values)<=nmax:
                msg='argument "{f}" requires between {nmin} and {nmax} arguments'.format(
                    f=self.dest,nmin=nmin,nmax=nmax)
                raise argparse.ArgumentTypeError(msg)
            setattr(args, self.dest, values)
    return RequiredLength

parser=argparse.ArgumentParser(prog='PROG')
parser.add_argument('-f', nargs='+', action=required_length(2,3))

args=parser.parse_args('-f 1 2 3'.split())
print(args.f)
# ['1', '2', '3']

try:
    args=parser.parse_args('-f 1 2 3 4'.split())
    print(args)
except argparse.ArgumentTypeError as err:
    print(err)
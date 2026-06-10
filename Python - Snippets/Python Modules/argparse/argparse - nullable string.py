"""
y, argparse - nullable string.py, 2019.11.19
https://stackoverflow.com/questions/55063560/replace-empty-strings-on-argparse-to-none
"""

import argparse


def nullable_string(val):
    if not val:
        return None
    return val


parser = argparse.ArgumentParser()
parser.add_argument('--foo', type=nullable_string)
parsed = parser.parse_args(['--foo', ''])
print(parsed)
print(parsed.foo)

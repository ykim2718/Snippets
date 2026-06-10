"""
y, argparse - returns none instead of [None].py, 2019.11.19
"""

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-foo', nargs='*', default=None, type=lambda x: None if x.lower() == 'none' else x)
parsed = parser.parse_args(['-foo', 'none'])
parsed = parser.parse_args([])
print(parsed)

# Still working, 2019.11.19
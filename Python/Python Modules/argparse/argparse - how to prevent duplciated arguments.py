"""
y, 2020.5.21
argparse - how to prevent duplciated arguments.py
https://stackoverflow.com/questions/23032514/argparse-disable-same-argument-occurrences/23032953#23032953
"""

import argparse


class UniqueStore(argparse.Action):
    def __call__(self, parser, namespace, values, option_string):
        if getattr(namespace, self.dest, self.default) is not self.default:
            parser.error(option_string + " appears several times.")
        setattr(namespace, self.dest, values)


parser = argparse.ArgumentParser()
parser.add_argument('-f', '--foo', action=UniqueStore)

# args = parser.parse_args()
args = parser.parse_args(" -f 1 -foo 2".split())


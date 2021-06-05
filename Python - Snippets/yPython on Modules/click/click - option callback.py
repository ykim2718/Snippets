"""
y, click - option callback.py, 2017.8.9
"""

import click
import os
import sys

def is_file(ctx, param, value):

    if not value or ctx.resilient_parsing:
        return None

    if os.path.isfile(value):
        return value
    else:
        return None

@click.command()
@click.option('-file_path', default=None, nargs=1, callback=is_file, help='file 2')
@click.option('-file3_path', default=None, nargs=1, help='file 3')
@click.argument('command', nargs=1)
def main2(command, file_path, file3_path):

    print('main 2 >>', command, file_path, file3_path)

@click.command()
@click.option('-file_path', default=None, nargs=1, callback=is_file, help='file 1')
@click.argument('command', nargs=1)
def main1(command, file_path):

    print('main 1 >>', command, file_path)

if __name__ == '__main__':

    print(sys.argv)
    eval(sys.argv[1] + '()')


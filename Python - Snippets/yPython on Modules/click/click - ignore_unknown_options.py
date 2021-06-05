"""
y, click - ignore_unknown_options.py, 2017.9.3
"""

import click
import sys

@click.group()
def y():
    pass


@y.command(context_settings=dict(
    ignore_unknown_options=True,))
@click.argument('plan_args', nargs=-1, type=click.UNPROCESSED)
def plan(plan_args):
    print('plan', plan_args)


@y.command()
def do():
    print('do')


@y.command()
def see():
    print('see')


if __name__ == '__main__':

    sys.argv += ['plan', 'abc', 'def']
    y()

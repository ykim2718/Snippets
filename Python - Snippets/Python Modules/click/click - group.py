"""
click - group.py, 2017.8.12

Comparing Python Command-Line Parsing Libraries - Argparse, Docopt, and Click
https://realpython.com/blog/python/comparing-python-command-line-parsing-libraries-argparse-docopt-click/

"""

import click


@click.group()
def greet():
    pass


@greet.command()
@click.argument('name')  # add the name argument
def hello(**kwargs):
    print('Hello, {0}!'.format(kwargs['name']))


@greet.command()
@click.argument('name')
def goodbye(**kwargs):
    print('Goodbye, {0}!'.format(kwargs['name']))


if __name__ == '__main__':
    import sys

    sys.argv += ['hello', 'Kyle']

    greet()

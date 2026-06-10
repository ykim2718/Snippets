"""
y, click - group2.py, 2017.8.12; 2021.1.19

Comparing Python Command-Line Parsing Libraries - Argparse, Docopt, and Click
https://realpython.com/blog/python/comparing-python-command-line-parsing-libraries-argparse-docopt-click/
"""

import click

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])


def greeter(**kwargs):
    output = '{0}, {1}!'.format(kwargs['greeting'],
                                kwargs['name'])
    if kwargs['caps']:
        output = output.upper()
    print(output)


@click.group(context_settings=CONTEXT_SETTINGS)
@click.version_option(version='1.0.0')
def greet():
    pass


@greet.command()
@click.argument('name')
@click.option('--greeting', default='Hello', help='word to use for the greeting')
@click.option('--caps', is_flag=True, help='uppercase the output')
def hello(**kwargs):
    greeter(**kwargs)


@greet.command()
@click.argument('name')
@click.option('--greeting', default='Goodbye', help='word to use for the greeting')
@click.option('--caps', is_flag=True, help='uppercase the output')
@click.option('--y', default='y')
def goodbye(**kwargs):
    print(kwargs['y'])
    greeter(**kwargs)


if __name__ == '__main__':
    import sys

    case = False
    if case == 'hello':
        sys.argv += ['hello', 'name here']
    elif case == 'goodbye':
        sys.argv += ['goodbye', 'name here', '--y', 'y^^....']
    elif case == 'help':
        sys.argv += ['-h']
    elif case is False:
        sys.argv += ['xxx']
    greet()


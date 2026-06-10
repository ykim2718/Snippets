"""
y, 2021.1.19
click - group with standalone.py
"""

import click

CONTEXT_SETTINGS = dict(help_option_names=['-h', '--help'])


@click.group(context_settings=CONTEXT_SETTINGS)
@click.version_option(version='0.0.0')
def greet():
    pass


@greet.command()
@click.argument('name')
@click.option('--to', default='world')
def hello(to):
    print(f"hello .. {to}")


@greet.command()
@click.option('--to', default='world')
def goodbye(to):
    print(f"goodbye .. {to}")


if __name__ == '__main__':
    import sys

    if False:
        sys.argv += ['hello', '--to', 'Johaquin Rodrigo']
    else:
        sys.argv += ['goodbye', '--to', 'Johaquin Rodrigo']
    greet(standalone_mode=False)
    print('You can see this if standalone_mode=False')

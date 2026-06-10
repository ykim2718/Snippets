"""
y, 2021.1.19
click - standalone_mode.py
"""

import click

@click.command()
@click.option('--to', default='world')
def hello(to):
    print(f"hello .. {to}")


if __name__ == '__main__':
    import sys

    sys.argv += ['--to', 'Johaquin Rodrigo']
    hello(standalone_mode=False)
    print('You can see this if standalone_mode=False')
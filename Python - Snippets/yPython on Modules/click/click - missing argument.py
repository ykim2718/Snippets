"""
y, click - missing argument.py, 2018.7.3
"""

import click

@click.command()
@click.option('-name', required=True, help='The person to greet.')
def hello(name):
    click.echo('Hello %s!' % name)

if __name__ == '__main__':
    hello()
"""
y, 2022.11.14
"""

import click


@click.command()
def hello():
    print('hello')


@click.command()
def hi():
    print('hi')


# hello()
hi()

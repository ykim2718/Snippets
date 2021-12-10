"""
y, 2021.12.10
click - group arguments.py
https://click.palletsprojects.com/en/8.0.x/commands/
"""

import click


@click.group()
@click.pass_context
def greet(ctx):
    ctx.ensure_object(str)


@greet.command()
@click.option('--to', default='world')
@click.pass_context
def hello(ctx, to):
    print(f"hello .. {to}")
    print(f"ctx.obj= {ctx.obj}")


@greet.command()
@click.option('--to', default='world')
def goodbye(to):
    print(f"goodbye .. {to}")


if __name__ == '__main__':

    import sys

    sys.argv += ['hello', '--to', 'Johaquin Rodrigo']
    greet(obj='^___^;;')
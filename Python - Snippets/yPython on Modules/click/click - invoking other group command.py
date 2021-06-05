"""
y, 2021.3.26
click - invoking other group command.py
https://click.palletsprojects.com/en/6.x/advanced/#invoking-other-commands
"""

import click

group1 = click.Group()
group2 = click.Group()


@group1.command()
@click.option('--bonus', default=1)
@click.option('--count', default=1)
def func1(bonus, count):
    click.echo(f"func1: bonus={bonus}, count={count}")


@group1.command()
def func2():
    click.echo(f"func2")


@group2.command()
@click.option('--bonus', default=100)
@click.option('--count', default=1)
@click.pass_context
def func3(ctx, bonus, count):
    click.echo(f"func3")
    ctx.forward(func1, count=count * 2)
    ctx.invoke(func1, count=count * 10)
    ctx.invoke(func1, bonus=7, count=count)
    ctx.invoke(func2)


if __name__ == '__main__':

    import sys

    sys.argv += ['func3', '--count', 9]
    group2()

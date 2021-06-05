"""
y, 2017.8.9; 2021.1.26, 2.3, 3.26
click - invoking other commands.py
https://click.palletsprojects.com/en/6.x/advanced/#invoking-other-commands
"""

import click

cli = click.Group()


@cli.command()
@click.option('--bonus', default=1)
@click.option('--count', default=1)
def func1(bonus, count):
    click.echo(f"func1: bonus={bonus}, count={count}")


@cli.command()
@click.option('--bonus', default=100)
@click.option('--count', default=1)
@click.pass_context
def func2(ctx, bonus, count):
    click.echo(f"func2")
    ctx.forward(func1, count=count * 2)
    ctx.invoke(func1, count=count * 10)
    ctx.invoke(func3)


@cli.command()
def func3():
    click.echo(f"func3")


if __name__ == '__main__':
    import sys

    sys.argv += ['func2', '--count', 9]
    cli()

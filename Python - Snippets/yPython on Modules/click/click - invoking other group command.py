"""
y, 2021.3.26, 12.18; 2022.4.17
click - invoking other group command.py
https://click.palletsprojects.com/en/6.x/advanced/#invoking-other-commands
"""

import click
import importlib

greeting = importlib.import_module('click - 1st')

group1 = click.Group()
group2 = click.Group()


@group1.command()
@click.option('--bonus', default=1)
@click.option('--count', default=1)
def func1(bonus, count):
    click.echo(f"g1.func1: bonus={bonus}, count={count}")


@group1.command()
def func2():
    click.echo(f"g1.func2")


@group2.command()
@click.option('--bonus', default=100)
@click.option('--count', default=1)
@click.pass_context
def func3(ctx, bonus, count):
    click.echo(f"g2.func3")
    ctx.forward(func1, count=count * 2)
    ctx.invoke(func1, count=count * 10)
    ctx.invoke(func1, bonus=7, count=count)
    ctx.invoke(func2)
    ctx.invoke(greeting.hello, name='Somerled 2021.12.18')


if __name__ == '__main__':

    args = ['func3', '--count', 9]
    group2(args=args)

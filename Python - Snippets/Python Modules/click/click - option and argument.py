"""
y, 2018.7.3; 2022.5.16 - 17
click - option and argument.py,
"""

import click
import sys


kwarg = 'my_kwarg'


@click.command()
@click.option('-opt', required=True, help='opt')
@click.option('-opt2', default=['opt2'], type=str, multiple=True)
@click.argument('arg')
@click.argument('arg2')
def hello(arg, opt, arg2, opt2, kwarg=kwarg, **kwargs):
    click.echo(f"{arg=}")
    click.echo(f"{opt=}")
    click.echo(f"{arg2=}")
    click.echo(f"{opt2=}")
    click.echo(f"{kwarg=}")
    click.echo(f"{kwargs=}")


if __name__ == '__main__':

    print(f"{click.__version__=}")  # '8.0.3'
    print(f"{hello.params=}")  # [<Option opt>, <Argument _arg>, <Argument _arg2>]
    if False:
        sys.argv[1:] = ['arg_', '-opt', 'opt_', 'arg2_']
        hello()
    else:
        # hello()  # error
        # hello(['arg_', '-opt', 'opt_', 'arg2_'])
        # hello(['-opt', 'opt_', 'arg_', 'arg2_'])
        hello(['-opt', 'opt_', 'arg_', 'arg2_', '-opt2', 'a', '-opt2', 'b'])

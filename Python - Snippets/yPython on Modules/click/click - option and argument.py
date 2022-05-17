"""
y, 2018.7.3; 2022.5.16
click - option and argument.py,
"""

import click
import sys


@click.command()
@click.option('-opt', required=True, help='opt')
@click.argument('arg')
@click.argument('arg2')
def hello(arg, opt, arg2, **kwargs):
    click.echo(f"{arg=}")
    click.echo(f"{opt=}")
    click.echo(f"{arg2=}")
    click.echo(f"{kwargs=}")


if __name__ == '__main__':

    print(f"{click.__version__=}")  # '8.0.3'
    print(f"{hello.params=}")  # [<Option opt>, <Argument _arg>, <Argument _arg2>]
    # FIXME !!!!!!!!!!!!!!!!!!!!!!!
    if False:
        sys.argv[1:] = ['arg.', '-opt', 'option.', 'arg2.']  # no working
        hello()
    else:
        # hello()  # error
        hello(['arg', '-opt', 'options..', 'arg2'])  # no working
        # hello(['arg..', '-opt', 'options..', 'arg2'])  # no working
        hello(['-opt', 'options..', 'arg2', 'extra'])  # no working

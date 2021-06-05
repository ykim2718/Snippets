"""
y, 2021.1.31
click - confirm (2).py
"""

import click


@click.group(context_settings=dict(help_option_names=['-h', '--help']))
def cli():
    pass


@cli.command()
def func():

    if click.confirm('-ok?', default=False, abort=False, show_default=True):
        click.echo('Yes, I am okay.')


if __name__ == '__main__':
    import sys

    sys.argv += ['func']
    cli()



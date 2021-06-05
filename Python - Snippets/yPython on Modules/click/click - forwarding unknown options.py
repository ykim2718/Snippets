"""
y, click - forwarding unknown options.py, 2017.8.13

Forwarding Unknown Options
http://click.pocoo.org/5/advanced/

"""

import click
import sys
from subprocess import call

@click.command(context_settings=dict(
    ignore_unknown_options=True,
))
@click.option('-v', '--verbose', is_flag=True, help='Enables verbose mode')
@click.argument('timeit_args', nargs=-1, type=click.UNPROCESSED)
def cli(verbose, timeit_args):
    """A wrapper around Python's timeit."""
    cmdline = ['python', '-mtimeit'] + list(timeit_args)
    if verbose:
        click.echo('Invoking: %s' % ' '.join(cmdline))
    call(cmdline)

cli()
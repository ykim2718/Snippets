"""
y, 2021.1.31
click - confirm.py
"""

import click


@click.group(context_settings=dict(help_option_names=['-h', '--help']))
def cli():
    pass


@cli.command()
@click.confirm('-ok?', default=False, abort=False, show_default=True)
def func():
    pass


if __name__ == '__main__':
    import sys

    sys.argv += ['func']
    cli()

    """
    -ok? [y/N]: 1
    Error: invalid input
    -ok? [y/N]: y
    Traceback (most recent call last):
      File "D:/Wolf/Homo academicus/yStudy on code - Python/Python - Snippets/yPython on Modules/click/click - confirm.py", line 15, in <module>
        @click.confirm('-ok', default=False, abort=False, show_default=True)
    TypeError: 'bool' object is not callable
    """
    # TODO 2021.1.31, How to remove TypeError ???

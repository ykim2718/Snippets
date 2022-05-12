"""
y, 2022.5.13
click - direct function call.py
https://stackoverflow.com/questions/68880149/how-to-self-invoke-python-click-cli-commands-without-context-invoke-or-context
"""

import click

@click.group()
def my_group():
    pass


@my_group.command()
@click.pass_context
@click.argument('my_arg')
def func(ctx, my_arg):

    print(f"{my_arg=}")


if __name__ == '__main__':

    func('hello ..')  # TODO 2022.5.13 !!! No working

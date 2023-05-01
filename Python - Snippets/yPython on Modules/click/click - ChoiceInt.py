"""
y, 2023.5.1
click - ChoiceInt.py
"""

import click


class CliChoiceInt(click.ParamType):
    """ y, 2023.5.1 """

    def __init__(self, choices=[]):
        """ y, 2023.5.1 """

        if not isinstance(choices, list):
            raise click.BadParameter(f"expected list argument but got {choices=}")
        if not all([isinstance(v, int) for v in choices]):
            raise click.BadParameter(f"expected int element in the list but got {choices=}")
        self.choices = choices

    def __repr__(self) -> str:
        """ y, 2023.5.1 """

        return f"CliChoiceInt({list(self.choices)})"

    def convert(self, value, param, ctx):
        """ y, 2023.5.1 """

        value = int(value)
        if value not in self.choices:
            raise click.BadOptionUsage(
                param.name, f"Invalid value for {param.get_error_hint(ctx)}: {value} is not one of {self.choices}")
        return value


@click.command()
@click.option('-choice', default=0, type=CliChoiceInt([0, 1, 2]))
# @click.option('-choice', default=0, type=CliChoiceInt(['0', '1', '2']))
def hello(choice):
    click.echo(f"{choice=} in hellow()")


if __name__ == '__main__':
    # hello()
    # hello(['-choice', '1'])
    hello(['-choice', '3'])

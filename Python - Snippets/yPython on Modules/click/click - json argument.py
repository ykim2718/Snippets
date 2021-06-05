"""
y, 2021.1.27
click - json argument.py
https://stackoverflow.com/questions/47631914/how-to-pass-several-list-of-arguments-to-click-option
"""

import click
import json


class JsonOption(click.Option):

    def type_cast_value(self, ctx, value):
        if self.type != click.STRING:
            raise click.BadParameter(f"need type=str but got type={self.type.name}")
        if value is None or not isinstance(value, str):
            raise click.BadParameter(f"{value} ... allowed only string")
        try:
            return json.loads(value)
        except Exception as ex:
            raise click.BadParameter(f"{value} ... {ex}")


@click.command(context_settings=dict(help_option_names=['-h', '--help']))
@click.option('--option1', cls=JsonOption)
@click.option('--option2', cls=JsonOption, default='[]')
@click.option('--option3', cls=JsonOption, default='[]', type=str)
def cli(option1, option2, option3):
    click.echo("Option 1, type: {}  value: {}".format(type(option1), option1))
    click.echo("Option 2, type: {}  value: {}".format(type(option2), option2))
    click.echo("Option 3, type: {}  value: {}".format(type(option3), option3))
    return 777


if __name__ == '__main__':
    import shlex
    import sys

    args = shlex.split('''
        --option1 '["o11", "o12", "o13"]' 
        --option2 '["o21", "o22", "o23"]'
        ''')
    if True:
        cli(args)
    else:
        sys.argv += args
        j = cli(standalone_mode=False)
        print(j)
    print('end ...')

"""
y, 2023.4.9
click - list argument.py
https://stackoverflow.com/questions/47631914/how-to-pass-several-list-of-arguments-to-click-option
"""

import click
import ast


class PythonLiteralOption(click.Option):

    def type_cast_value(self, ctx, value):
        try:
            return ast.literal_eval(value)
        except:
            raise click.BadParameter(value)


@click.command(context_settings=dict(help_option_names=['-h', '--help']))
@click.option('--option1', cls=PythonLiteralOption, default=[])
@click.option('--option2', cls=PythonLiteralOption, default=[])
def cli(option1, option2):
    click.echo("Option 1, type: {}  value: {}".format(
        type(option1), option1))
    click.echo("Option 2, type: {}  value: {}".format(
        type(option2), option2))


# do stuff
if __name__ == '__main__':
    import shlex

    a = '''
        --option1 '["o11", "o12", "o13"]' 
        --option2 "['o21', 'o22', 'o23']"
    '''
    cli(shlex.split(a))

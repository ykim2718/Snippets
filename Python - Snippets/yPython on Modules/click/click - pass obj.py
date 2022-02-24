"""
y, 2022.2.25
click - pass obj.py
https://click.palletsprojects.com/en/8.0.x/advanced/?highlight=ctx%20obj
"""

import click
import os


class Klass:
    def __init__(self, home=None):
        self.home = os.path.abspath(home or ".")
        print(f"{self.home=}")

    def __enter__(self):
        print('enter')
        return self

    def __exit__(self, exc_type, exc_value, tb):
        print('exit')


@click.group()
@click.option("--home", default=".home")
@click.pass_context
def cli(ctx, home):
    ctx.obj = ctx.with_resource(Klass(home))


@cli.command()
@click.pass_obj
def log(obj):

    click.echo(obj.home)


cli()


r"""
self.home='D:\\Wolf\\Homo academicus\\yStudy on code - Python\\Python - Snippets\\yPython on Modules\\click\\.home'
enter
D:\Wolf\Homo academicus\yStudy on code - Python\Python - Snippets\yPython on Modules\click\.home
exit
"""

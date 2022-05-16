"""
y, 2017.8.9: 2022.5.16
click - option callback.py,
"""

import click
import os


def is_file(ctx, param, value):
    if not value or ctx.resilient_parsing:
        return None

    if os.path.isfile(value):
        return value
    else:
        return None


@click.command()
@click.option('-file_path', default=None, nargs=1, callback=is_file, help='file 2')
@click.option('-file3_path', default=None, nargs=1, help='file 3')
@click.argument('command', nargs=1)
def main2(command, file_path, file3_path):
    print('main 2 >>', command, file_path, file3_path)


@click.command()
@click.option('-file_path', default=None, nargs=1, callback=is_file, help='file 1')
@click.argument('command', nargs=1)
def main1(command, file_path):
    print('main 1 >>', command, file_path)


if __name__ == '__main__':

    main1(['test1', '-file_path', __file__], standalone_mode=False)
    main2(['test2', '-file3_path', __file__], standalone_mode=False)

    """
    main 1 >> test1 D:\Wolf\Homo academicus\yStudy on code - Python\Python - Snippets\yPython on Modules\click\click - option callback.py
    main 2 >> test2 None D:\Wolf\Homo academicus\yStudy on code - Python\Python - Snippets\yPython on Modules\click\click - option callback.py
    """

"""
y, click - nargs.py, 2023.6.24

"""

import click


@click.command()
@click.option('-options', default=[1, 2], nargs=2, type=int)
def func(options):
    return ','.join([str(o) for o in options])


if __name__ == '__main__':

    print(f"{func([], standalone_mode=False)=}")  # '1,2'
    print(f"{func(['-options', '10', '20'], standalone_mode=False)=}")  # '10,20'

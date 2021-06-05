"""
y, click - ystudy on kwargs.py, 2017.8.12

"""

import sys
import click


@click.command()
@click.option('-arg1', help='')
@click.option('-kwarg1', default='default', nargs=1, help='')
def func(arg1, kwarg1='kwarg1'):

    print('main >>', arg1, kwarg1)


def main():
    pass

if __name__ == '__main__':

    del sys.argv[1:]
    # sys.argv += ['-arg1', '1', '-kwarg1', '2']
    sys.argv += ['-arg1', '1']
    func()


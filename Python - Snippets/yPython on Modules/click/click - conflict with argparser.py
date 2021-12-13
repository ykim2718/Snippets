"""
y, 2021.12.13
click - conflict with argparser.py
"""

import click


if __name__ == '__main__':

    import argparse
    parser = argparse.ArgumentParser(description='Process something.')
    if False:  # cause "unrecognized arguments" if True
        args = parser.parse_args()

    @click.group()
    def my_group():
        pass

    @my_group.command()
    def test():
        print('test() .. circument conflict between argparse and click')

    my_group()
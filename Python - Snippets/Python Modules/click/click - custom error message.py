"""
y, click - custom error message.py, 2017.8.22

Python Click: custom error message
https://stackoverflow.com/questions/39596070/python-click-custom-error-message
http://click.pocoo.org/5/api/

"""

import click
import sys


def modify_usage_error(command):
    """ y, 2017.8.22 """

    def show(self):

        click.echo('Error: %s\n' % self.format_message(), err=True)
        sys.argv = [sys.argv[0], "--help"]
        command()

    click.exceptions.UsageError.show = show


@click.group()
def greet():
    pass


modify_usage_error(greet)


@greet.command()
@click.argument('name')  # add the name argument
def hello(**kwargs):
    print('Hello, {0}!'.format(kwargs['name']))


@greet.command()
@click.argument('name')
def goodbye(**kwargs):
    print('Goodbye, {0}!'.format(kwargs['name']))

if __name__ == '__main__':

    import sys

    sys.argv += ['helloooo', 'Kyle']

    greet()

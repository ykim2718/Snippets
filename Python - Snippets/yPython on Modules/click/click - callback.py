"""
y, 2024.12.4
click - callback.py
"""

import click


def validate_commas(ctx, param, value):
    print(f"{param=}")
    if ',' not in value:
        raise click.BadParameter(f"The string contains no commas: {value=}")
    else:
        click.echo(f"The string contains {value.count(',')} commas.")
    return value


@click.command()
@click.option('--string', type=str, callback=validate_commas, help='A string with zero or more commas')
def main(string):
    print(string)


if __name__ == '__main__':
    main(['--string', 'Johaquin Rodrigo'])

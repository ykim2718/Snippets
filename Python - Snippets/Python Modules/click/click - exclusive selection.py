"""
y, 2025.4.13
click - exclusive selection.py
"""

import click


def validate_exclusive(ctx, param, value):
    """Custom validator to ensure exclusivity."""
    if value and any(ctx.params.get(other) for other in ['option2', 'option3'] if param.name != other):
        raise click.UsageError(f"Options are mutually exclusive: {param.name} cannot be used with other options.")
    return value


@click.command()
@click.option('--option1', is_flag=True, callback=validate_exclusive, help='Enable Option 1.')
@click.option('--option2', is_flag=True, callback=validate_exclusive, help='Enable Option 2.')
@click.option('--option3', is_flag=True, callback=validate_exclusive, help='Enable Option 3.')
def main(option1, option2, option3):
    if option1:
        click.echo("Option 1 selected.")
    elif option2:
        click.echo("Option 2 selected.")
    elif option3:
        click.echo("Option 3 selected.")
    else:
        click.echo("No option selected.")


if __name__ == '__main__':
    # main(['--option1', '--option2'])  # Option 1 selected.
    main(['--option2', '--option1'])  # Error: Options are mutually exclusive: option1 cannot be used with other options.

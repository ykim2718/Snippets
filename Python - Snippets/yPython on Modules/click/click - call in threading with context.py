"""
y, 2024.9.30
click - call in threading with context.py
"""

import threading
import click


@click.command()
@click.argument('name')
def greet(name):
    click.echo(f'Hello, {name}!')


def run_click_command_with_context(ctx):
    with ctx:
        ctx.invoke(greet, name='World')


@click.command()
@click.pass_context
def main(ctx):
    thread = threading.Thread(target=run_click_command_with_context, args=(ctx,))
    thread.start()
    thread.join()


if __name__ == '__main__':
    main()

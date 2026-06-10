"""
y, 2024.9.30
click - call in threading with CliRunner.py
"""

import click
import threading
from click.testing import CliRunner
import time


@click.command()
@click.argument('name')
def greet(name):
    click.echo(f'Hello, {name}!')


def run_click_command():
    runner = CliRunner()
    result = runner.invoke(greet, ['World'])
    print(f"{result.exit_code=}")
    print(f"{result.output=}")


thread = threading.Thread(target=run_click_command)
thread.start()
time.sleep(2)
thread.join()
print('.. end')

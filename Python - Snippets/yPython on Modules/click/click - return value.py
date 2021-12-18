"""
y, 2021.12.18
click - return value.py
https://stackoverflow.com/questions/26246824/how-do-i-return-a-value-when-click-option-is-used-to-pass-a-command-line-argume
"""

import sys
import click


@click.group(invoke_without_command=True)
@click.option('--option1')
@click.argument('arg1')
def main(option1, arg1):

    class SpecialObject():
        def __init__(self, option, arg):
            self.option = option
            self.arg = arg
        def __repr__(self):
            return str(self.option) + str(self.arg)

    return SpecialObject(option1, arg1)


@main.command()
def subcmd():
    return [4, 5, 6]


if __name__ == "__main__":

    commands = (
        ["--help"],
        ["arg_val", ],
        ["--option1", "option1_val", "arg1_val"],
        ["arg_val", "subcmd"],
        ["arg_val", "subcmd", "--help", ],
    )
    print(f'Click Version: {click.__version__}')
    print(f'Python Version: {sys.version}')
    for cmd in commands:
        print('-' * 64)
        print(f'Starting cmd:{cmd}')
        ret_val = main.main(cmd, standalone_mode=False)
        print(f"Returned: {type(ret_val)}, {ret_val}\n")

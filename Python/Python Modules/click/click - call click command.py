"""
y, 2022.5.13
click - call click command.py
https://localcoder.org/call-a-click-command-from-code
"""

import click


@click.group()
def click_group():
    pass


@click_group.command()
@click.pass_context
@click.option('-opt1', default=1)
@click.option('-opt2', default=2)
def func(ctx, opt1, opt2) -> int:
    return opt1 + opt2


def call_click_command(cmd, *args, **kwargs):
    """ Wrapper to call a click command
    y,  2022.5.13

    References
    ----------
    [1] https://localcoder.org/call-a-click-command-from-code
    """

    # Get positional arguments from args
    arg_values = {c.name: a for a, c in zip(args, cmd.params)}
    args_needed = {c.name: c for c in cmd.params if c.name not in arg_values}

    # build and check opts list from kwargs
    opts = {a.name: a for a in cmd.params if isinstance(a, click.Option)}
    for name in kwargs:
        if name in opts:
            arg_values[name] = kwargs[name]
        else:
            if name in args_needed:
                arg_values[name] = kwargs[name]
                del args_needed[name]
            else:
                raise click.BadParameter("Unknown keyword argument '{}'".format(name))

    # check positional arguments list
    for arg in (a for a in cmd.params if isinstance(a, click.Argument)):
        if arg.name not in arg_values:
            raise click.BadParameter("Missing required positional parameter '{}'".format(arg.name))

    # build parameter lists
    opts_list = sum([[o.opts[0], str(arg_values[n])] for n, o in opts.items()], [])
    args_list = [str(v) for n, v in arg_values.items() if n not in opts]

    # call the command
    result = cmd(opts_list + args_list, standalone_mode=False)

    # return
    return result


if __name__ == '__main__':

    print(f"{func.params=}")  # [<Option opt1>, <Option opt2>]
    print(f"{func(['-opt1', '10'], standalone_mode=False)=}")  # 12
    print(f"{func(['-opt1', '10', '-opt2', '20'], standalone_mode=False)=}")  # 30
    print(f"{call_click_command(func, 100, opt2=200)=}")  # 300

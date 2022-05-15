"""
y, 2022.5.15
click - call click command with ctx.py
https://localcoder.org/call-a-click-command-from-code
https://stackoverflow.com/questions/50077553/click-use-another-function-in-chained-commands-with-context-object
"""

import click


@click.group()
def my_group():
    pass


@my_group.command()
@click.pass_context
@click.option('-opt1', default=1)
@click.option('-opt2', default=10)
def func(ctx, opt1, opt2) -> int:
    if ctx.obj:
        print(f"{ctx.obj=}")
        my_value = ctx.obj['my_value']
    else:
        my_value = 0
    return opt1 + opt2 + my_value


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


def call_click_command_with_ctx(cmd, ctx, *args, **kwargs):
    """ Wrapper to call a click command with a Context object

    :param cmd: click cli command function to call
    :param ctx: click context
    :param args: arguments to pass to the function
    :param kwargs: keyword arguments to pass to the function
    :return: None
    """

    # monkey patch make_context
    def make_context(*some_args, **some_kwargs):
        child_ctx = click.Context(cmd, parent=ctx)
        with child_ctx.scope(cleanup=False):
            # cmd.parse_args(child_ctx, list(args))
            cmd.parse_args(child_ctx, some_args[-1])
            # cmd.parse_args(child_ctx, [])
        return child_ctx

    cmd.make_context = make_context
    prev_make_context = cmd.make_context

    # call the command
    result = call_click_command(cmd, *args, **kwargs)

    # restore make_context
    cmd.make_context = prev_make_context

    return result


if __name__ == '__main__':

    print(f"{func.params=}")  # [<Option opt1>, <Option opt2>]
    print(f"{func(['-opt1', '1'], standalone_mode=False)=}")  # 11
    print(f"{func(['-opt1', '2', '-opt2', '20'], standalone_mode=False)=}")  # 22
    print(f"{call_click_command(func, 3, opt2=30)=}")  # 33

    ctx = click.Context(func, parent=None, obj=dict(my_value=100, hello='click'))
    print(f"{call_click_command_with_ctx(func, ctx, 3, opt2=30)=}")  # 133
    print(f"{call_click_command_with_ctx(func, ctx, opt1=2, opt2=20)=}")  # 122
    print(f"{call_click_command_with_ctx(func, ctx)=}")  # KeyError: 'opt1'

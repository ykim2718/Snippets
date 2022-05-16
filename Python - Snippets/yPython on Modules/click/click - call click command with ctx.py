"""
y, 2022.5.15 - 16$
click - call click command with ctx.py
https://localcoder.org/call-a-click-command-from-code
https://stackoverflow.com/questions/50077553/click-use-another-function-in-chained-commands-with-context-object
"""

import click
import functools
import sys


@click.group()
def my_group():
    pass


@my_group.command()
@click.pass_context
@click.argument('arg', default=0, type=int)
@click.option('-opt1', default=1)
@click.option('-opt2', default=2)
def func(ctx, opt1, opt2, arg) -> int:
    if ctx.obj:
        print(f"{ctx.obj=}, {ctx.obj['callback']()=}")
    return arg + opt1 + opt2


def call_click_command(cmd, *args, **kwargs):
    """
    y,  2022.5.13, 5.16$

    References
    ----------
    [1] https://localcoder.org/call-a-click-command-from-code
    """

    options = {c.name: c for c in cmd.params}

    if args and isinstance(args[0], click.Context):
        my_context = args[0]
        args = tuple(args[1:])
    else:
        my_context = None

    f_name = sys._getframe(0).f_code.co_name
    if len(args) > len(options):
        raise click.BadParameter(f"{f_name}() takes {len(options)} but {len(args)} were given")
    if set(kwargs) > set(options):
        unknowns = set(kwargs) - set(options)
        raise click.BadParameter(f"{f_name}() got an unexpected keyword argument: {unknowns.pop()}")

    arguments = dict()
    for o, a in zip(options, args):
        arguments[o] = str(a)
    for k, v in kwargs.items():
        arguments[k] = str(v)
    for k, v in options.items():
        if k not in arguments:
            arguments[k] = str(v.default)

    def my_make_context(context, *args, **__):
        child_ctx = click.Context(cmd, parent=context)
        with child_ctx.scope(cleanup=False):
            cmd.parse_args(child_ctx, args[-1])
        return child_ctx

    arg_list = []
    kwarg_list = []
    for key, value in options.items():
        if isinstance(value, click.Argument):
            arg_list.append(arguments[key])
        elif isinstance(value, click.Option):
            kwarg_list.extend([value.opts[0], arguments[key]])

    if my_context:
        saved = cmd.make_context
        cmd.make_context = functools.partial(my_make_context, my_context, **arguments)
        result = cmd(arg_list + kwarg_list, standalone_mode=False)
        cmd.make_context = saved
    else:
        result = cmd(arg_list + kwarg_list, standalone_mode=False)
    return result


if __name__ == '__main__':

    print(f"{func.params=}")  # [<Argument arg>, <Option opt1>, <Option opt2>]
    print(f"{func(standalone_mode=False)=}")  # 3
    print(f"{func(['-opt2', '20'], standalone_mode=False)=}")  # 21
    print(f"{func(['10', '-opt2', '20'], standalone_mode=False)=}")  # 31
    print(f"{call_click_command(func)=}")  # 3
    print(f"{call_click_command(func, opt2=20)=}")  # 21
    print(f"{call_click_command(func, 10, opt2=20)=}")  # 31
    ctx = click.Context(func, parent=None, obj=dict(hello='click context', callback=lambda: 'my_callback'))
    print(f"{call_click_command(func, ctx)=}")  # 3
    print(f"{call_click_command(func, ctx, opt2=20)=}")  # 21
    print(f"{call_click_command(func, ctx, 10, opt2=20)=}")  # 31

    """
    func.params=[<Argument arg>, <Option opt1>, <Option opt2>]
    func(standalone_mode=False)=3
    func(['-opt2', '20'], standalone_mode=False)=21
    func(['10', '-opt2', '20'], standalone_mode=False)=31
    call_click_command(func)=3
    call_click_command(func, opt2=20)=21
    call_click_command(func, 10, opt2=20)=31
    ctx.obj={'hello': 'click context', 'callback': <function <lambda> at 0x000001BD18ADC430>}, ctx.obj['callback']()='my_callback'
    call_click_command(func, ctx)=3
    ctx.obj={'hello': 'click context', 'callback': <function <lambda> at 0x000001BD18ADC430>}, ctx.obj['callback']()='my_callback'
    call_click_command(func, ctx, opt2=20)=21
    ctx.obj={'hello': 'click context', 'callback': <function <lambda> at 0x000001BD18ADC430>}, ctx.obj['callback']()='my_callback'
    call_click_command(func, ctx, 10, opt2=20)=31
    """

"""
Y, 2016.4.15
Python Cookbook, David Beazley and Brian K. Jones, 3rd ed, 2013: pp.364-67.
9.16 Enforcing an Argument Signature on *args and *kwargs
"""

from inspect import Signature, Parameter

parms = [Parameter('x', Parameter.POSITIONAL_OR_KEYWORD),
         Parameter('y', Parameter.POSITIONAL_OR_KEYWORD, default=42),
         Parameter('z', Parameter.KEYWORD_ONLY, default=None)]
sig = Signature(parms)


def func(*args, **kwargs):
    bound_values = sig.bind(*args, **kwargs)
    for name, value in bound_values.arguments.items():
        print(name, value)


func(1, 2, z=3)
func(1)
func(1, z=3)
func(y=2, x=1)
# func(1,2,3,4)

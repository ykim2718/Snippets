"""
http://stackoverflow.com/questions/594266/equation-parsing-in-python
"""

import parser

formula = "sin(x)*x**2"
code = parser.expr(formula).compile()

from math import sin

x = 10
print(eval(code))

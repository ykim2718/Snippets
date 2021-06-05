'''
http://www.sympy.org/en/index.html
'''

from sympy import symbol as sym

a, b, bb, c = sym.symbols('a b bb c')
exp = (a + bb) * 40 - (c - a) / 0.5
r = exp.evalf(6, subs={a: 6, bb: 5, c: 2})
print(r)

from sympy.parsing.sympy_parser import parse_expr

exp = parse_expr('(a + bb ) * 40 - (c - a) / 0.5')
r = exp.evalf(subs={a: 6, b: 5, c: 2})
print(r)

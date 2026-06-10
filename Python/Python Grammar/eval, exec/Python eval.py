# y, 2016.4.8 - 14

import math

L = [0, 1, 0, 1]
D = {'a': 1, 'b': 2, 'cc': 3}
E = 24
F = 4

expressions = [
    'L[0] ^ L[1]',
    'L[0] & L[1]',
    'L[0] & ~L[1]',
    'L[0] ^ ((L[1]&L[2])& L[3])',
    "E - D['a'] - D['cc']",
    'F ^ 2',  # 4 ^ 2 = 6
    'F & 2',  # 4 & 2 = 0 ?????
    'pow(F,0.5)',
    'math.exp(-1)',
    '{2*(2+3)/2}',
    '1 and not 1',  # false, working ^^!!
    '4 and 2'  # 4 and 2 = 2 invalid boolean operation because variable > 1
]

for e in expressions:
    e = e.replace("{", "(")
    e = e.replace("}", ")")
    try:
        r = eval(e)
        print(e, "=", r)
    except Exception as ex:
        template = "[{0}] {1!r}"
        message = template.format(type(ex).__name__, ex.args)
        print(e, " ... ", message)
        pass

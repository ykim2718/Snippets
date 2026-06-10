"""
y, dis - disassemble.py, 2019.11.20
"""

import dis


def foo(a, b, c=3):
    print(a, b, c)


print(dis.dis(foo))

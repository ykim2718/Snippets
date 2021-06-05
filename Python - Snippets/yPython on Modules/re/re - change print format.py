"""
y, re - change print format.py, 2017.5.18

"""

import re

print_format1 = '{a:>8d} {b:>5d} {c:>5d} {d:>5.3f} {e:>7.3f} {f:>5.3f} {g:>4.2f} {h:>5.1f} {i:>6.4f}'
print_format2 = re.sub(r'({\w*:>\d)([.]?\d*[dfgs])(})', r'\1s\3', print_format1, count=99)
print(print_format1)
print(print_format2)  # expecting '{a:>8s} {b:>5s} {c:>5s} {d:>5s} {e:>5s} {f:>5s} {g:>4s} {h:>5s} {i:>6s}'
print(print_format1.format(a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7, i=8))
print(print_format2.format(a='The', b='tree', c='is', d='not', e='felled', f='by', g='the', h='first', i='blow.'))

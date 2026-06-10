"""
y, ast - literal_eval.py, 2018.10.3
https://docs.python.org/ko/3/library/ast.html#ast.literal_eval
"""

import ast
r = ast.literal_eval("{'muffin' : 'lolz', 'foo' : 'kitty'}")  # = {'muffin': 'lolz', 'foo': 'kitty'}
print(r)
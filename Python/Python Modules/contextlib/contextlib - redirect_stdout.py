"""
y, contextlib - redirect_stdout.py, 2018.5.16
https://docs.python.org/3/library/contextlib.html
"""

import io
from contextlib import redirect_stdout

f = io.StringIO()
with redirect_stdout(f):
    print('foobar')
    print(12)
print('Got stdout: "{0}"'.format(f.getvalue()))
f.close()  # y

# y idea
import os
with open(os.devnull, 'w') as f:
    with redirect_stdout(f):
        print('foobar')
        print(12)

"""
y, 2020.4.28
io - StringIO.py
https://docs.python.org/3/library/io.html#io.StringIO
"""

import io

output = io.StringIO()
output.write('First line.\n')
print('Second line.', file=output)

# Retrieve file contents -- this will be
# 'First line.\nSecond line.\n'
contents = output.getvalue()

# Close object and discard memory buffer --
# .getvalue() will now raise an exception.
output.close()

print('-' * 32)
print(contents)
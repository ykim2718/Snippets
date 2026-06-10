"""
y, 2020.8.24
tempfile - NameTemporaryFile.py
"""

import tempfile
import pathlib

data = b'1234567890'
f = tempfile.NamedTemporaryFile(delete=False)
f.write(data)
f.close()
del data

chunk_size = 4
with open(f.name, 'rb') as f:
    buffer = f.read(chunk_size)
    while buffer:
        print(buffer)
        buffer = f.read(chunk_size)
pathlib.Path(f.name).unlink()

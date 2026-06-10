"""
y, 2020.8.24
zlib - piecewise decompression of big data.py
https://stackoverflow.com/questions/1838699/how-can-i-decompress-a-gzip-stream-with-zlib
"""

import zlib
import tempfile
import pathlib
import numpy as np

big_data = np.arange(1024 * 1024 * 10)
temp_folder = r"d:\temp"
pathlib.Path(temp_folder).mkdir(parents=True, exist_ok=True)
with tempfile.NamedTemporaryFile(delete=False, dir=temp_folder) as f:
    compressed = zlib.compress(big_data)
    f.write(compressed)
    del compressed

chunk_size = 1024 * 1024
d = zlib.decompressobj(zlib.MAX_WBITS | 32)
# d = zlib.decompressobj(16 + zlib.MAX_WBITS)  # NOT WORKING
with open(f.name, 'rb') as f, tempfile.NamedTemporaryFile(delete=False, dir=temp_folder) as g:
    buffer = f.read(chunk_size)
    while buffer:
        g.write(d.decompress(buffer))
        buffer = f.read(chunk_size)
pathlib.Path(f.name).unlink()
local_file_path = pathlib.Path(g.name)

array = local_file_path.read_bytes()
array = np.frombuffer(array, dtype=big_data.dtype)
print(type(array), array.shape, array.dtype, f"matched={np.array_equal(big_data, array)}")
print(array[:5])

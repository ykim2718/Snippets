"""
y, 2020.11.18
zlib - python object.py
"""

import zlib
import pickle

obj = dict(a=1, b=2)
pickled = pickle.dumps(obj)
compressed = zlib.compress(pickled, level=-1)

decompressed = zlib.decompress(compressed)
unpickled = pickle.loads(decompressed)
print(f"unpickled={unpickled}")
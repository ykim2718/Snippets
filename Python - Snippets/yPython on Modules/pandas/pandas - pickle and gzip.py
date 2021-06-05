"""
y, 2020.5.1
pandas - pickle and gzip.py
"""

import pandas as pd
import gzip
import pickle

frame = pd.DataFrame([1, 2, float('nan')], columns=['A'])
frame._metadata = dict(array=[10, 20])
print(frame, frame._metadata)
pickled = pickle.dumps(frame)
zipped = gzip.compress(pickled)
print(f"len(zipped)={len(zipped)}")
pickled = gzip.decompress(zipped)
frame = pickle.loads(pickled)
print(frame, frame._metadata)
"""
y, 2024.2.6
tqdm - multi-lines.py
"""

import tqdm
import time

kwargs = dict(position=0, leave=True)

for i in tqdm.tqdm(range(3)):
    time.sleep(0.1)
    for j in tqdm.tqdm(range(2), **kwargs):
        time.sleep(0.1)
"""
y, 2020.8.25, 9.11
tqdm - basic.py
https://github.com/tqdm/tqdm
https://tqdm.github.io/docs/tqdm/
    >> ncols: The width of the entire output message
"""

import tqdm
import time

with tqdm.tqdm(total=100, ncols=80, desc='updating', unit='byte') as pbar:
    for j in range(10):
        time.sleep(0.1)
        pbar.update(10)

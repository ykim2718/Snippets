"""
y, 2020.8.25, 9.11; 2022.5.17, 7.5
tqdm - basic.py
https://github.com/tqdm/tqdm
https://tqdm.github.io/docs/tqdm/
    >> ncols: The width of the entire output message
"""

import tqdm
import time

with tqdm.tqdm(total=100, ncols=80, desc='updating', unit='byte') as pbar:
    for j in range(10):
        pbar.update(10)
        time.sleep(0.1)


for i in tqdm.tqdm(range(10), desc='disable=True', disable=True):
    time.sleep(0.1)


pbar = tqdm.tqdm(range(10), desc='trange()')
for i in pbar:
    pbar.set_description(f"{pbar.n=}")
    time.sleep(0.1)

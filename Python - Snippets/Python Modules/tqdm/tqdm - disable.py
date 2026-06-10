"""
y, 2020.3.5
tqdm - disable.py
"""

from tqdm import tqdm
import time

for j in tqdm(range(9), disable=True):
    time.sleep(0.2)
    print(j)
print('end')

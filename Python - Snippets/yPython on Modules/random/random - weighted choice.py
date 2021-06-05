"""
y, random - weighted choice.py, 2019.10.11
https://docs.python.org/3/library/random.html#random.choices
"""

import random
import numpy as np


random.seed(777)
population = list('abcdef')
weights = [0, 1, 2, 3, 4, 5]
iteration = 1000  # batch_count
batch_size = 3
batches = np.empty((iteration, batch_size), dtype=str)
for j in range(iteration):
    result = random.choices(population, weights=weights, k=batch_size)
    batches[j, :] = result

# print(batches)
bins, counts = np.unique(batches.flat, return_counts=True)  # batches.flat or .flatten()
print(bins)
print(counts/counts.min())